#pragma once
#include <iostream>
#include "PlockY/Block.hpp"
#include <vector>
#include <set>
#include <memory>
#include "PlockY/Step.hpp"
#include "PlockY/DenseBlock.hpp"
#include "PlockY/Strategy.hpp"
#include "PlockY/Regrouper.hpp"

namespace PlockY {
    
    enum class BlockSpec {
        Normal,
        Transpose
    };

    template <typename BlockType>
    class BlockMatrix {
    private:

        using MatrixType = typename BlockType::MatrixType;
        static_assert(std::is_base_of<Block<MatrixType>, BlockType>::value, "BlockType must be a subclass of Block");
        
        std::vector<MatrixType> LHS;
        std::vector<MatrixType> CORR;
        std::vector<std::tuple<int, int, std::shared_ptr<BlockType>, BlockSpec>> blocks;


        MatrixType regroup_indices(std::vector<std::vector<std::tuple<int,int>>> step){
            std::vector<MatrixType> res;
            for (const auto& row : step) {
                std::vector<MatrixType> row_mat;
                for (const auto& block : row) {
                    auto blockPtr = getBlock(std::get<0>(block), std::get<1>(block));
                    auto type = getType(std::get<0>(block), std::get<1>(block));
                    if (blockPtr == nullptr) {
                        throw std::runtime_error("Block not found");
                    }
                    if (type == BlockSpec::Transpose){
                        row_mat.push_back(blockPtr->getMatrix().transpose());
                    }else if(type == BlockSpec::Normal){
                        row_mat.push_back(blockPtr->getMatrix());
                    }else{
                        throw std::runtime_error("Unsupported block type");
                    }
                }

                res.push_back(MatrixConcatenator<MatrixType>::concatenateHorizontally(row_mat));
            }
            return MatrixConcatenator<MatrixType>::concatenateVertically(res);
        }

        bool isValidStrategy(const Strategy& strat) const {
            std::set<int> blockSet;
            for (const auto& block : blocks) {
                blockSet.insert(std::get<0>(block));
                blockSet.insert(std::get<1>(block));
            }

            std::vector<int> mergedAndSorted(blockSet.begin(), blockSet.end());

            return strat.get_merged() == mergedAndSorted;
        }
        
    public:
        BlockMatrix() = default;

        void setBlock(int row, int col, std::unique_ptr<BlockType> block, BlockSpec type) {
            blocks.push_back(std::make_tuple(row, col, std::move(block),type));
        }
        void setBlock(int row, int col, std::shared_ptr<BlockType> block, BlockSpec type) {
            blocks.push_back(std::make_tuple(row, col, std::move(block),type));
        }
        
        std::shared_ptr<BlockType> getBlock(int row, int col) const { 
            for (const auto& block : blocks) {
                if (std::get<0>(block) == row && std::get<1>(block) == col) {
                    return std::get<2>(block) ;
                }
            }
            return nullptr;
        }

        BlockSpec getType(int row, int col) const {
            for (const auto& block : blocks) {
                if (std::get<0>(block) == row && std::get<1>(block) == col) {
                    return std::get<3>(block);
                }
            }
            return BlockSpec::Normal;
        }

        bool isValid() const {
            std::unordered_map<int, int> rowSizes;
            std::unordered_map<int, int> colSizes;

            for (const auto& block : blocks) {
                int row = std::get<0>(block);
                int col = std::get<1>(block);
                auto blockPtr = std::get<2>(block);

                if (rowSizes.count(row) && rowSizes[row] != blockPtr->getRows()) {
                    return false;
                }
                rowSizes[row] = blockPtr->getRows();

                if (colSizes.count(col) && colSizes[col] != blockPtr->getCols()) {
                    return false;
                }
                colSizes[col] = blockPtr->getCols();
            }


            // checks if blocks are unique
            std::set<std::pair<int, int>> blockPairs;
            for (const auto& block : blocks) {
                blockPairs.insert({std::get<0>(block), std::get<1>(block)});
            }

            if (blockPairs.size() != blocks.size()) return false;

            return true;
        }

        void regroup(const Strategy& strategy) {
            
            if (!isValidStrategy(strategy)){
                throw std::runtime_error("Strategy not valid for the matrix");
            }

            LHS.clear();
            CORR.clear();
            auto LHS_steps = strategy.get_LHS_indices();

            for (const auto& step : LHS_steps) {
                LHS.push_back( regroup_indices(step) );
            }
   
            auto RHS_steps = strategy.get_RHS_indices();
            for (const auto& step : RHS_steps) {
                CORR.push_back( regroup_indices(step));
            }
        }

        void print() const {
            for (const auto& block : blocks) {
                if (std::get<3>(block) == BlockSpec::Transpose) {
                    std::cout << "Transpose: Block at position (" << std::get<0>(block) << ", " << std::get<1>(block) << ") count :" << std::get<2>(block).use_count() <<std::endl;
                    std::get<2>(block)->print();
                } else {
                    std::cout << "Normal: Block at position (" << std::get<0>(block) << ", " << std::get<1>(block) << ") count :" << std::get<2>(block).use_count() <<std::endl;
                    std::get<2>(block)->print();
                }
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