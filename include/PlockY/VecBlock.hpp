#pragma once

#include "PlockY/Block.hpp"

namespace PlockY
{
    template <typename Scalar>
    class VecBlock : public Block<Eigen::Matrix<Scalar, Eigen::Dynamic, 1>>{ 
    private:
        // trick per fare override di metodi con firma diversa, ha senso? è una buona pratica?
        Scalar get(size_t row, size_t col ) const override { return this->matrix(row, col); }
        void set(size_t row, size_t col , const Scalar& value) override { this->matrix(row, col) = value; }

    public:
        using MatrixType = Eigen::Matrix<Scalar, Eigen::Dynamic, 1>;

        // Constructor
        VecBlock() : Block<Eigen::Matrix<Scalar, Eigen::Dynamic, 1>>() {}
        VecBlock(size_t rows) : Block<Eigen::Matrix<Scalar, Eigen::Dynamic, 1>>(rows,1) {};
        VecBlock(const Eigen::Matrix<Scalar, Eigen::Dynamic, 1>& matrix) : Block<Eigen::Matrix<Scalar, Eigen::Dynamic, 1>>(matrix) {}; 

        // Implement operations for dense blocks
        Scalar get(size_t row) const { return this->matrix(row); }
        void set(size_t row, const Scalar& value) { this->matrix(row) = value; }

        BlockTypeEnum getType() const override { return BlockTypeEnum::Vec; }

        void print() const override {
            std::cout << this->matrix << std::endl;
        }

    };  
}

