#pragma once
#include <iostream>
#include "Eigen/Dense"
#include <vector>
#include "PlockY/Strategy.hpp"
#include <memory>
#include <numeric>
#include "PlockY/VecBlock.hpp"

namespace PlockY {
    template <typename Scalar>
    class BlockVector {
        static_assert(std::is_arithmetic<Scalar>::value, "Scalar must be a numeric type");
    private:
        std::vector<std::tuple<int, std::shared_ptr<VecBlock<Scalar>>>> vec_blocks;

        std::vector<Eigen::Matrix<Scalar, Eigen::Dynamic, 1>> RHS;

        Eigen::Matrix<Scalar, Eigen::Dynamic, 1> regroup_vectors(std::vector<int> step) {
            Eigen::Matrix<Scalar, Eigen::Dynamic, 1> res = Eigen::Matrix<Scalar, Eigen::Dynamic, 1>::Zero(0);
            for (const auto& pos : step) {
                auto blockPtr = getBlock(pos);
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

    public:
        BlockVector() = default;

        void setBlock(int pos, std::unique_ptr<VecBlock<Scalar>> block) {
            vec_blocks.push_back(std::make_tuple(pos, std::move(block)));
        }

        std::shared_ptr<VecBlock<Scalar>> getBlock(int pos) const {
            for (const auto& block : vec_blocks) {
                if (std::get<0>(block) == pos) {
                    return std::get<1>(block);
                }
            }
            return nullptr;
        }

        void regroup(const Strategy& strategy) {
            auto steps = strategy.get_steps();
            for (const auto& step : steps) {
                RHS.push_back( regroup_vectors(step.get_block_pos()));
            }
        }

        void print() {
            for (const auto& block : vec_blocks) {
                std::cout << "Position: " << std::get<0>(block) << std::endl;
                std::cout << "Block: " << std::endl;
                std::get<1>(block)->print();
            }
        }

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

        const Eigen::Matrix<Scalar, Eigen::Dynamic, 1>& get_rhs(int i) const {
            return RHS[i];
        }

        const Eigen::Matrix<Scalar, Eigen::Dynamic, 1> get_rhs_compl(const Strategy& strategy, const Step& step) const {
            Eigen::Matrix<Scalar, Eigen::Dynamic, 1> res = Eigen::Matrix<Scalar, Eigen::Dynamic, 1>::Zero(0);
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

        std::string to_string() {
            std::string res = "";
            for (const auto& block : vec_blocks) {
                res += vectoString(std::get<1>(block)->getMatrix()) + "\n";
            }
            return res;
        }

        static std::string vectoString(const Eigen::Matrix<Scalar, Eigen::Dynamic, 1>& mat){
            std::stringstream ss;
            ss << mat;
            return ss.str();
        }
    
    };
}