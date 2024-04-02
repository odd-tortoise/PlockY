#pragma once

#include "PlockY/Block.hpp"

namespace PlockY
{
    template <typename Scalar>
    class DenseBlock : public Block<DenseBlock<Scalar>, Scalar>
    {
        static_assert(std::is_arithmetic<Scalar>::value, "Scalar must be a numeric type");

    public:
        // Constructor
        DenseBlock(int rows, int cols) : Block<DenseBlock<Scalar>, Scalar>(rows, cols), matrix(rows, cols) {}

        // Implement operations for dense blocks
        Scalar getImpl(int row, int col) const { return matrix(row, col); }
        void setImpl(int row, int col, const Scalar& value) { matrix(row, col) = value; }

        void setMatrix(const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>& matrix)
        {
            // Check that the matrix has the correct size
            if (matrix.rows() != this->getRows() || matrix.cols() != this->getCols())
            {
                throw std::invalid_argument("Matrix size does not match block size");
            }

            // Assign the input matrix to the block's matrix
            this->matrix = matrix;
        }

        BlockType getType() const override { return BlockType::Dense; }

        const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>& getMatrix() const { return matrix; }
   
    private:
        Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> matrix;
    };

}