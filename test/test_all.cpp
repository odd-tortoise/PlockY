#include <catch2/catch_test_macros.hpp>
#include "PlockY/Block.hpp"
#include "PlockY/MTXBlockLoaderFactory.hpp"
#include "PlockY/DenseBlock.hpp"
#include "PlockY/SparseBlock.hpp"
#include "PlockY/VecBlock.hpp"
#include "PlockY/AbstractBlockLoaderFactory.hpp"
#include "PlockY/BlockMatrixLoader.hpp"
#include "PlockY/BlockVectorLoader.hpp"
#include "PlockY/BlockMatrix.hpp"

// Test for DenseBlock Initialization and Type Check
TEST_CASE("DenseBlock Initialization and Type Check", "[DenseBlock]") {
    Eigen::MatrixXd denseMatrix(2, 2);
    denseMatrix << 1, 2, 3, 4;

    PlockY::DenseBlock<double> denseBlock(denseMatrix);
    REQUIRE(denseBlock.getType() == PlockY::BlockTypeEnum::Dense);
}

// Test for DenseBlock Setting and Getting a Value
TEST_CASE("DenseBlock Setting and Getting a Value", "[DenseBlock]") {
    Eigen::MatrixXd denseMatrix(2, 2);
    denseMatrix << 1, 2, 3, 4;

    PlockY::DenseBlock<double> denseBlock(denseMatrix);
    denseBlock.set(1, 1, 10.0);
    REQUIRE(denseBlock.get(1, 1) == 10.0);
}

// Test for DenseBlock Retrieving the Matrix
TEST_CASE("DenseBlock Retrieving the Matrix", "[DenseBlock]") {
    Eigen::MatrixXd denseMatrix(2, 2);
    denseMatrix << 1, 2, 3, 4;

    PlockY::DenseBlock<double> denseBlock(denseMatrix);
    Eigen::MatrixXd retrievedMatrix = denseBlock.getMatrix();
    REQUIRE(retrievedMatrix == denseMatrix);
    REQUIRE(denseBlock.getCols() == denseMatrix.cols());
    REQUIRE(denseBlock.getRows() == denseMatrix.rows());
}

// Test for SparseBlock Initialization and Type Check
TEST_CASE("SparseBlock Initialization and Type Check", "[SparseBlock]") {
    Eigen::SparseMatrix<double> sparseMatrix(2, 2);
    sparseMatrix.insert(0, 0) = 1;
    sparseMatrix.insert(1, 1) = 4;

    PlockY::SparseBlock<double> sparseBlock(sparseMatrix);
    REQUIRE(sparseBlock.getType() == PlockY::BlockTypeEnum::Sparse);
}

// Test for SparseBlock Setting and Getting a Value
TEST_CASE("SparseBlock Setting and Getting a Value", "[SparseBlock]") {
    Eigen::SparseMatrix<double> sparseMatrix(2, 2);
    sparseMatrix.insert(0, 0) = 1;
    sparseMatrix.insert(1, 1) = 4;

    /*PlockY::SparseBlock<double> sparseBlock(sparseMatrix);
    sparseBlock.set(0, 0, 10.0);
    REQUIRE(sparseBlock.get(0, 0) == 10.0);*/
}

// Test for SparseBlock Retrieving the Matrix
TEST_CASE("SparseBlock Retrieving the Matrix", "[SparseBlock]") {
    Eigen::SparseMatrix<double> sparseMatrix(2, 2);
    sparseMatrix.insert(0, 0) = 1;
    sparseMatrix.insert(1, 1) = 4;

    PlockY::SparseBlock<double> sparseBlock(sparseMatrix);
    Eigen::SparseMatrix<double> retrievedMatrix = sparseBlock.getMatrix();
    REQUIRE(retrievedMatrix.nonZeros() == sparseMatrix.nonZeros());

    for (int k = 0; k < sparseMatrix.outerSize(); ++k) {
        for (Eigen::SparseMatrix<double>::InnerIterator it(sparseMatrix, k); it; ++it) {
            REQUIRE(it.value() == retrievedMatrix.coeff(it.row(), it.col()));
        }
    }

    REQUIRE(sparseBlock.getCols() == sparseMatrix.cols());
    REQUIRE(sparseBlock.getRows() == sparseMatrix.rows());
}

// Helper function to create a temporary Matrix Market file for testing
void createTempMTXFile(const std::string& filePath, const std::string& content) {
    std::ofstream file(filePath);
    file << content;
    file.close();
}

TEST_CASE("MTXBlockLoader creates DenseBlock correctly", "[MTXBlockLoader]") {
    const std::string filePath = "dense_test.mtx";
    const std::string content = "%%MatrixMarket matrix array real general\n2 2\n1.0\n2.0\n3.0\n4.0\n";
    createTempMTXFile(filePath, content);

    PlockY::MTXBlockLoader<double> factory;
    auto denseBlock = factory.createDense(filePath, 0, 0);

    REQUIRE(denseBlock->getType() == PlockY::BlockTypeEnum::Dense);
    Eigen::MatrixXd matrix = denseBlock->getMatrix();
    REQUIRE(matrix(0, 0) == 1.0);
    REQUIRE(matrix(0, 1) == 3.0);
    REQUIRE(matrix(1, 0) == 2.0);
    REQUIRE(matrix(1, 1) == 4.0);
}

TEST_CASE("MTXBlockLoader creates SparseBlock correctly", "[MTXBlockLoader]") {
    const std::string filePath = "sparse_test.mtx";
    const std::string content = "%%MatrixMarket matrix coordinate real general\n2 2 4\n1 1 1.0\n1 2 2.0\n2 1 3.0\n2 2 4.0\n";
    createTempMTXFile(filePath, content);

    PlockY::MTXBlockLoader<double> factory;
    auto sparseBlock = factory.createSparse(filePath, 0, 0);

    REQUIRE(sparseBlock->getType() == PlockY::BlockTypeEnum::Sparse);
    Eigen::SparseMatrix<double> matrix = sparseBlock->getMatrix();
    REQUIRE(matrix.coeff(0, 0) == 1.0);
    REQUIRE(matrix.coeff(0, 1) == 2.0);
    REQUIRE(matrix.coeff(1, 0) == 3.0);
    REQUIRE(matrix.coeff(1, 1) == 4.0);
}

TEST_CASE("MTXBlockLoader creates VectorBlock correctly", "[MTXBlockLoader]") {
    const std::string filePath = "vector_test.mtx";
    const std::string content = "%%MatrixMarket matrix array real general\n4 1\n1.0\n2.0\n3.0\n4.0\n";
    createTempMTXFile(filePath, content);

    PlockY::MTXBlockLoader<double> factory;
    auto vectorBlock = factory.createVector(filePath, 0);

    REQUIRE(vectorBlock->getType() == PlockY::BlockTypeEnum::Vec);
    Eigen::MatrixXd matrix = vectorBlock->getMatrix();
    REQUIRE(matrix(0, 0) == 1.0);
    REQUIRE(matrix(1, 0) == 2.0);
    REQUIRE(matrix(2, 0) == 3.0);
    REQUIRE(matrix(3, 0) == 4.0);
}

TEST_CASE("BlockMatrixLoader correctly reads and parses .blk files and constructs matrices") {
    SECTION("Load dense block matrix from .blk file") {
        std::string blkFilePath = "data/blk_files/5b5_withNonSquareBlocks_dense.blk";
        auto blockMatrix = PlockY::BlockMatrixLoader::load<PlockY::DenseBlock<double>>(blkFilePath);

        REQUIRE(blockMatrix.isValid());
        REQUIRE(blockMatrix.getBlock(0, 0) != nullptr);
        REQUIRE(blockMatrix.getBlock(1, 1) != nullptr);
    }

    SECTION("Load sparse block matrix from .blk file") {
        std::string blkFilePath = "data/blk_files/5b5_withNonSquareBlocks_sparse.blk";
        auto blockMatrix = PlockY::BlockMatrixLoader::load<PlockY::SparseBlock<double>>(blkFilePath);

        REQUIRE(blockMatrix.isValid());
        REQUIRE(blockMatrix.getBlock(0, 0) != nullptr);
        REQUIRE(blockMatrix.getBlock(1, 1) != nullptr);
    }
}

TEST_CASE("BlockMatrix integrity and placement verification") {
    SECTION("Dense block matrix placement and integrity") {
        std::string blkFilePath = "data/blk_files/5b5_withNonSquareBlocks_dense.blk";
        auto blockMatrix = PlockY::BlockMatrixLoader::load<PlockY::DenseBlock<double>>(blkFilePath);

        REQUIRE(blockMatrix.isValid());

        // Verify the placement and integrity
        auto block = blockMatrix.getBlock(0, 0);
        REQUIRE(block != nullptr);
        REQUIRE(block->getMatrix().rows() == 4);
        REQUIRE(block->getMatrix().cols() == 4);

        block = blockMatrix.getBlock(1, 1);
        REQUIRE(block != nullptr);
        REQUIRE(block->getMatrix().rows() == 2);
        REQUIRE(block->getMatrix().cols() == 2);
    }

    SECTION("Sparse block matrix placement and integrity") {
        std::string blkFilePath = "data/blk_files/5b5_withNonSquareBlocks_sparse.blk";
        auto blockMatrix = PlockY::BlockMatrixLoader::load<PlockY::SparseBlock<double>>(blkFilePath);

        REQUIRE(blockMatrix.isValid());

        // Verify the placement and integrity
        auto block = blockMatrix.getBlock(0, 0);
        REQUIRE(block != nullptr);
        REQUIRE(block->getMatrix().rows() == 4);
        REQUIRE(block->getMatrix().cols() == 4);

        block = blockMatrix.getBlock(1, 1);
        REQUIRE(block != nullptr);
        REQUIRE(block->getMatrix().rows() == 2);
        REQUIRE(block->getMatrix().cols() == 2);
    }

    SECTION("Vector block matrix placement and integrity") {
        std::string blkFilePath = "data/blk_files/5b5guess.vblk";
        auto blockVector = PlockY::BlockVectorLoader::load<PlockY::VectorBlock<double>>(blkFilePath);

        // Verify the placement and integrity
        auto block = blockVector.getBlock(0);
        REQUIRE(block != nullptr);
        REQUIRE(block->getMatrix().rows() == 4);
    }
}
