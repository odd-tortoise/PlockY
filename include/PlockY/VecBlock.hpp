#pragma once

#include "PlockY/Block.hpp"

namespace PlockY
{
    template <typename Scalar>
    class VectorBlock : public Block<Eigen::Matrix<Scalar, Eigen::Dynamic, 1>>{ 

    public:
        using MatrixType = Eigen::Matrix<Scalar, Eigen::Dynamic, 1>;

        // Constructor
        VectorBlock() : Block<MatrixType>() {}
        VectorBlock(const MatrixType& matrix) : Block<MatrixType>(matrix) {}; 

        // Implement operations for dense blocks
        Scalar get(size_t row) const { return this->matrix(row); }
        void set(size_t row, const Scalar& value) { this->matrix(row) = value; }
        Scalar get(size_t row, size_t col ) const override { 
            if (col != 0){
                throw std::invalid_argument("Column index out of bounds");
            }
            return this->matrix(row, col); 
        }

        void set(size_t row, size_t col , const Scalar& value) override { 
            if (col != 0){
                throw std::invalid_argument("Column index out of bounds");
            }
            this->matrix(row, col) = value; 
        }

        BlockTypeEnum getType() const override { return BlockTypeEnum::Vec; }

        void print() const override {
            std::cout << this->matrix << std::endl;
        }

    };  
}

