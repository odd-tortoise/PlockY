#pragma once

#include "Block.hpp"

namespace PlockY
{
    template <typename Scalar>
    class SparseBlock : public Block<Eigen::SparseMatrix<Scalar>>{ 
    public:
        using MatrixType = Eigen::SparseMatrix<Scalar>;

        // Constructor
        SparseBlock() : Block<MatrixType>() {}
        SparseBlock(const MatrixType& matrix) : Block<MatrixType>(matrix) {};

        // Implement operations for sparse blocks
        Scalar get(size_t row, size_t col) const override { return this->matrix.coeff(row, col); }
        void set(size_t row, size_t col, const Scalar& value) override { this->matrix.insert(row, col) = value; }

        BlockTypeEnum getType() const override { return BlockTypeEnum::Sparse; }

        void print() const override {
            std::cout << "SparseBlock" << std::endl;
            for (int i = 0; i < this->rows; i++) {
                for (int j = 0; j < this->cols; j++) {
                    std::cout << this->matrix.coeff(i, j) << " ";
                }
                std::cout << std::endl;
            }
        }    
    };  
}