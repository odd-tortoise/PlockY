#pragma once

#include "Block.hpp"

namespace PlockY
{
    template <typename Scalar>
    class DenseBlock : public Block<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>>{ 
    public:
        using MatrixType = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;

        // Constructor
        DenseBlock() : Block<MatrixType>() {}
        DenseBlock(const MatrixType& matrix) : Block<MatrixType>(matrix) {}; 

        // Implement operations for dense blocks
        Scalar get(size_t row, size_t col) const override { return this->matrix(row, col); }
        void set(size_t row, size_t col, const Scalar& value) override { this->matrix(row, col) = value; }

        BlockTypeEnum getType() const override { return BlockTypeEnum::Dense; }

        void print() const {
            std::cout << this->matrix << std::endl;
        }
    };  
}
