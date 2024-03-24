#pragma once

#include "PlockY/Block.hpp"

namespace PlockY
{
    template <typename Scalar>
    class DenseBlock : public Block<Scalar>{ 
    public:
        // Constructor
        DenseBlock(int rows, int cols) : Block<Scalar>(rows, cols), matrix(rows, cols) {}

        // Implement operations for dense blocks
        Scalar get(int row, int col) const override { return matrix(row, col); }
        void set(int row, int col, const Scalar& value) override { matrix(row, col) = value; }

    private:
        Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> matrix;
    };  
}

