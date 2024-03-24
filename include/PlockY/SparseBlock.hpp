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

    private:
        Eigen::SparseMatrix<Scalar> matrix;
    };  
}