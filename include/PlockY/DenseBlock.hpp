#pragma once

#include "PlockY/Block.hpp"

namespace PlockY
{
    template <typename Scalar>
    class DenseBlock : public Block<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>>{ 
    public:
        using MatrixType = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;


        // Constructor
        DenseBlock() : Block<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>>() {}
        DenseBlock(size_t rows, size_t cols) : Block<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>>(rows,cols) {};
        DenseBlock(const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>& matrix) : Block<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>>(matrix) {}; 

        // Implement operations for dense blocks
        Scalar get(size_t row, size_t col) const override { return this->matrix(row, col); }
        void set(size_t row, size_t col, const Scalar& value) override { this->matrix(row, col) = value; }

        BlockTypeEnum getType() const override { return BlockTypeEnum::Dense; }

        void print() const {
            std::cout << this->matrix << std::endl;
        }
    };  
}
