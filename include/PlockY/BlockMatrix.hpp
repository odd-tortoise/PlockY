#pragma once
#include <iostream>
#include "PlockY/Block.hpp"
#include <vector>
#include <memory>
#include "PlockY/Step.hpp"
#include "PlockY/DenseBlock.hpp"
#include "PlockY/Strategy.hpp"
//#include "PlockY/regroup_helper.hpp"

namespace PlockY {
    template <typename BlockType>
    class BlockMatrix {
    
    private:
        using MatrixType = typename BlockType::MatrixType;
        static_assert(std::is_base_of<Block<MatrixType>, BlockType>::value, "BlockType must be a subclass of Block");
        std::vector<MatrixType> LHS;
        std::vector<MatrixType> CORR;
        std::vector<std::tuple<int, int, std::shared_ptr<BlockType>>> blocks;

        /*
        MatrixType regroup_dense(std::vector<std::vector<std::tuple<int,int>>> step){
            std::vector<std::vector<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>>> res;
            for (const auto& row : step) {
                std::vector<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>> row_mat;
                for (const auto& block : row) {
                    auto blockPtr = getBlock(std::get<0>(block), std::get<1>(block));
                    if (blockPtr == nullptr) {
                        throw std::runtime_error("Block not found");
                    }
                    auto denseBlock = std::dynamic_pointer_cast<DenseBlock<Scalar>>(blockPtr);
                    if (denseBlock == nullptr) {
                        throw std::runtime_error("Block is not dense");
                    }
                    row_mat.push_back(denseBlock->getMatrix());
                }
                res.push_back(row_mat);
            }
            return PlockYHelper::concatenateVecOfVec<Scalar>(res);
        }
        */
        
    public:
        BlockMatrix() = default;

        void setBlock(int row, int col, std::unique_ptr<BlockType> block) {
            blocks.push_back(std::make_tuple(row, col, std::move(block)));
        }
        
        std::shared_ptr<BlockType> getBlock(int row, int col) const { 
            for (const auto& block : blocks) {
                if (std::get<0>(block) == row && std::get<1>(block) == col) {
                    return std::get<2>(block) ;
                }
            }
            return nullptr;
        }
   
        bool isValid() const {  
            // Check if all the rows and columns are homogeneous in size
            // all the blocks in the same row should have the same number of rows
            // all the blocks in the same column should have the same number of columns
            return true;
        }
/*
        void regroup(const Strategy& strategy) {
            auto LHS_steps = strategy.get_LHS_indices();

            for (const auto& step : LHS_steps) {
                LHS.push_back( regroup_dense(step));
            }
   
            auto RHS_steps = strategy.get_RHS_indices();
            for (const auto& step : RHS_steps) {
                CORR.push_back( regroup_dense(step));
            }
        }
*/
        void print() const {
            for (const auto& block : blocks) {
                std::cout << "Block at position (" << std::get<0>(block) << ", " << std::get<1>(block) << ")" << std::endl;
                std::get<2>(block)->print();
            }
        }

        const MatrixType& get_lhs(int i) const {
            return LHS[i];
        }

        const MatrixType& get_corr(int i) const {
            return CORR[i];
        }
    };    
} // namespace PlockY