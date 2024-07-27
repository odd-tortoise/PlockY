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

