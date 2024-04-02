#pragma once

#include <vector>
#include "Plocky/Block.hpp"

namespace PlockY
{

template <typename Scalar>
    class SparseBlock : public Block<SparseBlock<Scalar>, Scalar>
    {
        static_assert(std::is_arithmetic<Scalar>::value, "Scalar must be a numeric type");

    public:
        // Constructor
        SparseBlock(int rows, int cols) : Block<SparseBlock<Scalar>, Scalar>(rows, cols), matrix(rows, cols) {}

        // Implement operations for dense blocks
        Scalar getImpl(int row, int col) const { return matrix.coeff(row, col); }
        void setImpl(int row, int col, const Scalar& value) { matrix.insert(row, col) = value; }
        void setMatrix(const Eigen::SparseMatrix<Scalar>& matrix) {
            // Check that the matrix has the correct size
            if (matrix.rows() != this->getRows() || matrix.cols() != this->getCols()) {
                throw std::invalid_argument("Matrix size does not match block size");
            }

            // Assign the input matrix to the block's matrix
            this->matrix = matrix;
        }

        BlockType getType() const override { return BlockType::Sparse; }

    private:
        Eigen::SparseMatrix<Scalar> matrix;
    };
} // namespace PlockY