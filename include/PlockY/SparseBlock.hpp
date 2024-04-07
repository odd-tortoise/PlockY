#pragma once

#include <vector>
#include "Plocky/Block.hpp"

namespace PlockY
{
    template <typename Scalar>
    class SparseBlock : public Block<Scalar>
    { 
    public:
        // Constructor
        SparseBlock(int rows, int cols) : Block<Scalar>(rows, cols), matrix(rows, cols) {}

        // Implement operations for sparse blocks
        Scalar get(int row, int col) const override { return matrix.coeff(row, col); }
        void set(int row, int col, const Scalar& value) override { matrix.insert(row, col) = value; }

        void setMatrix(const Eigen::SparseMatrix<Scalar>& matrix) {
            // Check that the matrix has the correct size
            if (matrix.rows() != this->getRows() || matrix.cols() != this->getCols()) {
                throw std::invalid_argument("Matrix size does not match block size");
            }

            // Assign the input matrix to the block's matrix
            this->matrix = matrix;
        }

        
        BlockType getType() const override { return BlockType::Sparse; }

        const Eigen::SparseMatrix<Scalar>& getMatrix() const { return matrix; }   

    private:
        Eigen::SparseMatrix<Scalar> matrix;
    };  
}