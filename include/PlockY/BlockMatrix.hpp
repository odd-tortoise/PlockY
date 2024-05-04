#pragma once
#include <iostream>
#include "PlockY/Block.hpp"
#include <vector>
#include <memory>
#include "PlockY/Step.hpp"
#include "PlockY/DenseBlock.hpp"
#include "PlockY/Strategy.hpp"
#include "PlockY/regroup_helper.hpp"

namespace PlockY {
    template <typename Scalar>
    class BlockMatrix {
        static_assert(std::is_arithmetic<Scalar>::value, "Scalar must be a numeric type");
    private:
        std::vector<std::tuple<int, int, std::shared_ptr<Block<Scalar>>>> blocks;
        Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> regroup_dense(std::vector<std::vector<std::tuple<int,int>>> step){
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

        std::vector<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>> LHS;
        std::vector<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>> CORR;
        
    public:
        BlockMatrix() = default;

        void setBlock(int row, int col, std::unique_ptr<Block<Scalar>> block) {
            blocks.push_back(std::make_tuple(row, col, std::move(block)));
        }
        
        std::shared_ptr<Block<Scalar>> getBlock(int row, int col) const { 
            for (const auto& block : blocks) {
                if (std::get<0>(block) == row && std::get<1>(block) == col) {
                    return std::get<2>(block) ;
                }
            }
            return nullptr;
        }
   
        bool isValid() const {
            return true;
            //Check if all the rows and columns are homogeneous 
        }

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

        void print() const {
            for (const auto& block : blocks) {
                std::cout << "Block at position (" << std::get<0>(block) << ", " << std::get<1>(block) << ")" << std::endl;
                std::get<2>(block)->print();
            }
        }

        const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>& get_lhs(int i) const {
            return LHS[i];
        }

        const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>& get_corr(int i) const {
            return CORR[i];
        }
    };
    
} // namespace PlockY