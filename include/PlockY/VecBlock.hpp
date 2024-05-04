#pragma once

#include "PlockY/Block.hpp"

namespace PlockY
{
    template <typename Scalar>
    class VecBlock : public Block<Scalar>{ 
    public:
        // Constructor
        VecBlock(int rows) : Block<Scalar>(rows, 1), vec(rows) {}

        // Implement operations for dense blocks
        Scalar get(int row, int col) const override { return vec(row); }
        void set(int row,int col, const Scalar& value) override { vec(row) = value; }

        void setMatrix(const Eigen::Matrix<Scalar, Eigen::Dynamic,1>& matrix) {
            // Check that the matrix has the correct size
            if ( matrix.rows() != this->getRows() || matrix.cols() != this->getCols() ){
                throw std::invalid_argument("Matrix size does not match block size");
            }

            // Assign the input matrix to the block's matrix
            this->vec = matrix;
        }

        const Eigen::Matrix<Scalar, Eigen::Dynamic,1>& getMatrix() const { return vec; }   

        BlockType getType() const override { return BlockType::Vec; }

        void print() const {
            std::cout << vec << std::endl;
        }

    private:
        Eigen::Matrix<Scalar, Eigen::Dynamic, 1> vec;
    };  
}

