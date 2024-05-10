#pragma once
#include <iostream>
#include "Eigen/Dense"
#include <vector>
#include "PlockY/Strategy.hpp"
#include <memory>
#include <numeric>
#include "PlockY/VecBlock.hpp"

namespace PlockY {
    template <typename BlockType>
    class BlockVector {
    private:
        using MatrixType = typename BlockType::MatrixType;
        static_assert(std::is_base_of<Block<MatrixType>, BlockType>::value, "BlockType must be a subclass of Block");
        
        std::vector<std::tuple<int, std::shared_ptr<BlockType>>> vec_blocks;
        std::vector<MatrixType> RHS;
        
        MatrixType regroup_indices(std::vector<int> step) {
            std::vector<MatrixType> res;
            for (const auto& pos : step) {
                auto blockPtr = getBlock(pos);
                if (blockPtr == nullptr) {
                    throw std::runtime_error("Block not found");
                }
                res.push_back(blockPtr->getMatrix());
            }
            return MatrixConcatenator<MatrixType>::concatenateVertically(res);
        }

    public:
        BlockVector() = default;

        void setBlock(int pos, std::unique_ptr<BlockType> block) {
            vec_blocks.push_back(std::make_tuple(pos, std::move(block)));
        }

        std::shared_ptr<BlockType> getBlock(int pos) const {
            for (const auto& block : vec_blocks) {
                if (std::get<0>(block) == pos) {
                    return std::get<1>(block);
                }
            }
            return nullptr;
        }

        void regroup(const Strategy& strategy) {
            RHS.clear();
            auto steps = strategy.get_steps();
            for (const auto& step : steps) {
                RHS.push_back( regroup_indices(step.get_block_pos()));
            }
        }

        void print() {
            for (const auto& block : vec_blocks) {
                std::cout << "Position: " << std::get<0>(block) << " Block: " << std::endl;
                std::get<1>(block)->print();
            }
        }

/*
        void update(const Step& step, int i, const Eigen::Matrix<Scalar, Eigen::Dynamic, 1>& u_star) {
            int start = 0;
            for (const auto& pos : step.get_block_pos()) {
                for (auto& tuple : vec_blocks) {
                    if (std::get<0>(tuple) == pos) {
                        std::get<1>(tuple)->setMatrix((u_star.segment(start, this->getBlock(pos)->getRows())));
                        start += this->getBlock(pos)->getRows();
                    }
                }
            }
            RHS[i] = u_star;
        }
*/

        const MatrixType& get_rhs(int i) const {
            return RHS[i];
        }

/*
        const MatrixType get_rhs_compl(const Strategy& strategy, const Step& step) const {
            MatrixType res = MatrixType::Zero(0);
            auto indices = strategy.get_complementary_blocks(step);

            for (const auto& index : indices) {
                auto blockPtr = getBlock(index);
                if (blockPtr == nullptr) {
                    throw std::runtime_error("Block not found");
                }
                auto vecBlock = std::dynamic_pointer_cast<VecBlock<Scalar>>(blockPtr);
                if (vecBlock == nullptr) {
                    throw std::runtime_error("Block is not dense");
                }
                Eigen::Matrix<Scalar, Eigen::Dynamic, 1> block = vecBlock->getMatrix();
                Eigen::Matrix<Scalar, Eigen::Dynamic, 1> temp = Eigen::Matrix<Scalar, Eigen::Dynamic, 1>::Zero(res.size() + block.size());
                temp << res, block;
                res = temp;
            }

            return res;
        }
*/


        //utility function to convert the block vector to string for debugging
        std::string to_string() {
            std::string res = "";
            for (const auto& block : vec_blocks) {
                res += vectoString(std::get<1>(block)->getMatrix()) + "\n";
            }
            return res;
        }
        static std::string vectoString(const MatrixType& mat){
            std::stringstream ss;
            ss << mat;
            return ss.str();
        }
    
    };
}