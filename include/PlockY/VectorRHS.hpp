#pragma once
#include <iostream>
#include "Eigen/Dense"
#include <vector>
#include <memory>

namespace PlockY {
    template <typename Scalar>
    class VectorRHS {
        static_assert(std::is_arithmetic<Scalar>::value, "Scalar must be a numeric type");
    private:
        std::vector<std::tuple<int, std::shared_ptr<Eigen::VectorXd>>> vector_blocks;

    public:
        VectorRHS() = default;

        void setBlock(int pos, std::shared_ptr<Eigen::VectorXd> block) {
            vector_blocks.push_back(std::make_tuple(pos, block));
        }

        std::shared_ptr<Eigen::VectorXd> getBlock(int pos) {
            for (const auto& block : vector_blocks) {
                if (std::get<0>(block) == pos) {
                    return std::get<1>(block);
                }
            }
            return nullptr;
        }

        void print() {
            std::cout << "Vector length: " << vector_blocks.size() << std::endl;

            for (const auto& blockTuple : vector_blocks) {
                int pos = std::get<0>(blockTuple);
                std::shared_ptr<Eigen::VectorXd> block = std::get<1>(blockTuple);

                std::cout << "Block at (" << pos << "): ";
                if (block) {
                    std::cout << *block << std::endl;
                } else {
                    std::cout << "Empty Block" << std::endl;
                }
            }
        }
    };
}