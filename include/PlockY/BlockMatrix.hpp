#pragma once
#include <iostream>
#include "PlockY/Block.hpp"
#include <vector>
#include <memory>
#include "PlockY/Step.hpp"
#include "PlockY/DenseBlock.hpp"
#include "PlockY/Strategy.hpp"
//#include "PlockY/regroup_helper.hpp"
#include "PlockY/Regrouper.hpp"

namespace PlockY {
    template <typename BlockType>
    class BlockMatrix {
    
    private:
        using MatrixType = typename BlockType::MatrixType;
        static_assert(std::is_base_of<Block<MatrixType>, BlockType>::value, "BlockType must be a subclass of Block");
        std::vector<MatrixType> LHS;
        std::vector<MatrixType> CORR;
        std::vector<std::tuple<int, int, std::shared_ptr<BlockType>>> blocks;

        MatrixType regroup_indices(std::vector<std::vector<std::tuple<int,int>>> step){
            std::vector<MatrixType> res;
            for (const auto& row : step) {
                std::vector<MatrixType> row_mat;
                for (const auto& block : row) {
                    std::shared_ptr<BlockType>  blockPtr = getBlock(std::get<0>(block), std::get<1>(block));
                    std::cout << "Type of blockPtr: " << typeid(blockPtr).name() << std::endl;
                    std::cout << "Block at position (" << std::get<0>(block) << ", " << std::get<1>(block) << ")";
                    if (blockPtr == nullptr) {
                        throw std::runtime_error("Block not found");
                    }
                    row_mat.push_back(blockPtr->getMatrix());
                    std::cout<< " size "<<blockPtr->getMatrix().rows()<<"x"<<blockPtr->getMatrix().cols()<<std::endl;
                }

                res.push_back(MatrixConcatenator<MatrixType>::concatenateHorizontally(row_mat));
            }
            return MatrixConcatenator<MatrixType>::concatenateVertically(res);
        }
        
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

        void regroup(const Strategy& strategy) {
            auto LHS_steps = strategy.get_LHS_indices();

            for (const auto& step : LHS_steps) {
                LHS.push_back( regroup_indices(step));
            }
   
            auto RHS_steps = strategy.get_RHS_indices();
            for (const auto& step : RHS_steps) {
                CORR.push_back( regroup_indices(step));
            }
        }

        void print() const {
            for (const auto& block : blocks) {
                std::cout << "Block at position (" << std::get<0>(block) << ", " << std::get<1>(block) << ")" << std::endl;
                std::cout << "Type of blockPtr: " << typeid(std::get<2>(block)).name() << std::endl;
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