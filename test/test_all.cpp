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
#include "PlockY/Step.hpp"
#include "PlockY/Strategy.hpp"
#include "PlockY/Solver.hpp"
#include "PlockY/Regrouper.hpp"

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

// Testing correct creation of matrices
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
        std::string blkFilePath = "../data/blk_files/5b5_withNonSquareBlocks_dense.blk";
        auto blockMatrix = PlockY::BlockMatrixLoader::load<PlockY::DenseBlock<double>>(blkFilePath);

        REQUIRE(blockMatrix.isValid());
        REQUIRE(blockMatrix.getBlock(0, 0) != nullptr);
        REQUIRE(blockMatrix.getBlock(1, 1) != nullptr);
    }

    SECTION("Load sparse block matrix from .blk file") {
        std::string blkFilePath = "../data/blk_files/5b5_withNonSquareBlocks_sparse.blk";
        auto blockMatrix = PlockY::BlockMatrixLoader::load<PlockY::SparseBlock<double>>(blkFilePath);

        REQUIRE(blockMatrix.isValid());
        REQUIRE(blockMatrix.getBlock(0, 0) != nullptr);
        REQUIRE(blockMatrix.getBlock(1, 1) != nullptr);
    }
}

TEST_CASE("BlockMatrix integrity and placement verification") {
    SECTION("Dense block matrix placement and integrity") {
        std::string blkFilePath = "../data/blk_files/5b5_withNonSquareBlocks_dense.blk";
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
        std::string blkFilePath = "../data/blk_files/5b5_withNonSquareBlocks_sparse.blk";
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
        std::string blkFilePath = "../data/blk_files/5b5guess.vblk";
        auto blockVector = PlockY::BlockVectorLoader::load<PlockY::VectorBlock<double>>(blkFilePath);

        // Verify the placement and integrity
        auto block = blockVector.getBlock(0);
        REQUIRE(block != nullptr);
        REQUIRE(block->getMatrix().rows() == 4);
    }
}

// Testing Step methods
TEST_CASE("Step Class test") {
    PlockY::Step step_1({1, 2, 3});

    auto step1_blocks = step_1.get_block_pos();
    REQUIRE(step1_blocks.size() == 3);
    REQUIRE(step1_blocks[0] == 1);
    REQUIRE(step1_blocks[1] == 2);
    REQUIRE(step1_blocks[2] == 3);

}

// Testing strategy methods
TEST_CASE("Strategy Creation and Methods") {
    PlockY::Step step_1({0, 3});
    PlockY::Step step_2({1});
    PlockY::Step step_3({2});
    std::vector<PlockY::Step> steps = {step_1, step_2, step_3};

    PlockY::Strategy strategy(steps);

    SECTION("Check Steps") {
        const auto& retrievedSteps = strategy.get_steps();
        REQUIRE(retrievedSteps.size() == 3);
        REQUIRE(retrievedSteps[0].get_block_pos() == std::vector<int>({0, 3}));
        REQUIRE(retrievedSteps[1].get_block_pos() == std::vector<int>({1}));
        REQUIRE(retrievedSteps[2].get_block_pos() == std::vector<int>({2}));
    }

    SECTION("Check Merged Vector") {
        const auto& mergedVector = strategy.get_merged();
        REQUIRE(mergedVector == std::vector<int>({0, 1, 2, 3}));
    }

    SECTION("Check Complementary Blocks") {
        const auto& comple1 = strategy.get_complementary_blocks(0);
        REQUIRE(comple1 == std::vector<int>({1, 2}));

        const auto& comple2 = strategy.get_complementary_blocks(1);
        REQUIRE(comple2 == std::vector<int>({0, 2, 3}));

        const auto& comple3 = strategy.get_complementary_blocks(2);
        REQUIRE(comple3 == std::vector<int>({0, 1, 3}));
    }

    SECTION("Check LHS Indices") {
        const auto& LHS_indices = strategy.get_LHS_indices();
        REQUIRE(LHS_indices.size() == 3);

        REQUIRE(LHS_indices[0].size() == 2); // 2x2 matrix
        REQUIRE(LHS_indices[0][0].size() == 2);
        REQUIRE(LHS_indices[0][1].size() == 2);
        REQUIRE(LHS_indices[0][0][0] == std::make_tuple(0, 0));
        REQUIRE(LHS_indices[0][0][1] == std::make_tuple(0, 3));
        REQUIRE(LHS_indices[0][1][0] == std::make_tuple(3, 0));
        REQUIRE(LHS_indices[0][1][1] == std::make_tuple(3, 3));

        REQUIRE(LHS_indices[1].size() == 1); // 1x1 matrix
        REQUIRE(LHS_indices[1][0].size() == 1);
        REQUIRE(LHS_indices[1][0][0] == std::make_tuple(1, 1));

        REQUIRE(LHS_indices[2].size() == 1); // 1x1 matrix
        REQUIRE(LHS_indices[2][0].size() == 1);
        REQUIRE(LHS_indices[2][0][0] == std::make_tuple(2, 2));
    }

    SECTION("Check RHS Indices") {
        const auto& RHS_indices = strategy.get_RHS_indices();
        REQUIRE(RHS_indices.size() == 3);

        REQUIRE(RHS_indices[0].size() == 2); // 2x2 matrix
        REQUIRE(RHS_indices[0][0].size() == 2);
        REQUIRE(RHS_indices[0][1].size() == 2);
        REQUIRE(RHS_indices[0][0][0] == std::make_tuple(0, 1));
        REQUIRE(RHS_indices[0][0][1] == std::make_tuple(0, 2));
        REQUIRE(RHS_indices[0][1][0] == std::make_tuple(3, 1));
        REQUIRE(RHS_indices[0][1][1] == std::make_tuple(3, 2));

        REQUIRE(RHS_indices[1].size() == 1); // 1x3 matrix
        REQUIRE(RHS_indices[1][0].size() == 3);
        REQUIRE(RHS_indices[1][0][0] == std::make_tuple(1, 0));
        REQUIRE(RHS_indices[1][0][1] == std::make_tuple(1, 2));
        REQUIRE(RHS_indices[1][0][2] == std::make_tuple(1, 3));

        REQUIRE(RHS_indices[2].size() == 1); // 1x3 matrix
        REQUIRE(RHS_indices[2][0].size() == 3);
        REQUIRE(RHS_indices[2][0][0] == std::make_tuple(2, 0));
        REQUIRE(RHS_indices[2][0][1] == std::make_tuple(2, 1));
        REQUIRE(RHS_indices[2][0][2] == std::make_tuple(2, 3));
    }
}

// Testing regrouper methods
TEST_CASE("Regrouper Dense Matrix Horizontal Concatenation") {
    Eigen::MatrixXd mat1(2, 2);
    mat1 << 1, 2,
            3, 4;
    
    Eigen::MatrixXd mat2(2, 2);
    mat2 << 5, 6,
            7, 8;

    std::vector<Eigen::MatrixXd> matrices = {mat1, mat2};

    Eigen::MatrixXd result = PlockY::MatrixConcatenator<Eigen::MatrixXd>::concatenateHorizontally(matrices);

    REQUIRE(result.rows() == 2);
    REQUIRE(result.cols() == 4);
    REQUIRE(result(0, 0) == 1);
    REQUIRE(result(0, 1) == 2);
    REQUIRE(result(0, 2) == 5);
    REQUIRE(result(0, 3) == 6);
    REQUIRE(result(1, 0) == 3);
    REQUIRE(result(1, 1) == 4);
    REQUIRE(result(1, 2) == 7);
    REQUIRE(result(1, 3) == 8);
}

TEST_CASE("Regrouper Dense Matrix Vertical Concatenation") {
    Eigen::MatrixXd mat1(2, 2);
    mat1 << 1, 2,
            3, 4;
    
    Eigen::MatrixXd mat2(2, 2);
    mat2 << 5, 6,
            7, 8;

    std::vector<Eigen::MatrixXd> matrices = {mat1, mat2};

    Eigen::MatrixXd result = PlockY::MatrixConcatenator<Eigen::MatrixXd>::concatenateVertically(matrices);

    REQUIRE(result.rows() == 4);
    REQUIRE(result.cols() == 2);
    REQUIRE(result(0, 0) == 1);
    REQUIRE(result(0, 1) == 2);
    REQUIRE(result(2, 0) == 5);
    REQUIRE(result(2, 1) == 6);
}

TEST_CASE("Regrouper Sparse Matrix Horizontal Concatenation") {
    Eigen::SparseMatrix<double> mat1(2, 2);
    mat1.insert(0, 0) = 1;
    mat1.insert(0, 1) = 2;
    mat1.insert(1, 0) = 3;
    mat1.insert(1, 1) = 4;
    
    Eigen::SparseMatrix<double> mat2(2, 2);
    mat2.insert(0, 0) = 5;
    mat2.insert(0, 1) = 6;
    mat2.insert(1, 0) = 7;
    mat2.insert(1, 1) = 8;

    std::vector<Eigen::SparseMatrix<double>> matrices = {mat1, mat2};

    Eigen::SparseMatrix<double> result = PlockY::MatrixConcatenator<Eigen::SparseMatrix<double>>::concatenateHorizontally(matrices);

    REQUIRE(result.rows() == 2);
    REQUIRE(result.cols() == 4);
    REQUIRE(result.coeff(0, 0) == 1);
    REQUIRE(result.coeff(0, 1) == 2);
    REQUIRE(result.coeff(0, 2) == 5);
    REQUIRE(result.coeff(0, 3) == 6);
    REQUIRE(result.coeff(1, 0) == 3);
    REQUIRE(result.coeff(1, 1) == 4);
    REQUIRE(result.coeff(1, 2) == 7);
    REQUIRE(result.coeff(1, 3) == 8);
}

TEST_CASE("Regrouper Sparse Matrix Vertical Concatenation") {
    Eigen::SparseMatrix<double> mat1(2, 2);
    mat1.insert(0, 0) = 1;
    mat1.insert(0, 1) = 2;
    mat1.insert(1, 0) = 3;
    mat1.insert(1, 1) = 4;
    
    Eigen::SparseMatrix<double> mat2(2, 2);
    mat2.insert(0, 0) = 5;
    mat2.insert(0, 1) = 6;
    mat2.insert(1, 0) = 7;
    mat2.insert(1, 1) = 8;

    std::vector<Eigen::SparseMatrix<double>> matrices = {mat1, mat2};

    Eigen::SparseMatrix<double> result = PlockY::MatrixConcatenator<Eigen::SparseMatrix<double>>::concatenateVertically(matrices);

    REQUIRE(result.rows() == 4);
    REQUIRE(result.cols() == 2);
    REQUIRE(result.coeff(0, 0) == 1);
    REQUIRE(result.coeff(0, 1) == 2);
    REQUIRE(result.coeff(2, 0) == 5);
    REQUIRE(result.coeff(2, 1) == 6);
}

TEST_CASE("Regrouper Dense Vector Vertical Concatenation") {
    Eigen::VectorXd vec1(2);
    vec1 << 1, 2;
    
    Eigen::VectorXd vec2(2);
    vec2 << 3, 4;

    std::vector<Eigen::VectorXd> vectors = {vec1, vec2};

    Eigen::VectorXd result = PlockY::MatrixConcatenator<Eigen::VectorXd>::concatenateVertically(vectors);

    REQUIRE(result.size() == 4);
    REQUIRE(result(0) == 1);
    REQUIRE(result(1) == 2);
    REQUIRE(result(2) == 3);
    REQUIRE(result(3) == 4);
}