#pragma once

#include "Block.hpp"

namespace PlockY
{
    /**
     * @brief A class representing a dense block matrix based on Eigen's Matrix type.
     *
     * It provides methods to get and set elements in the dense matrix, as well as
     * to print the matrix.
     *
     * @tparam Scalar The data type of the elements in the dense matrix.
     */
    template <typename Scalar>
    class DenseBlock : public Block<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>> { 
    public:
        using MatrixType = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;

        /**
         * @brief Default constructor.
         *
         * Initializes an empty DenseBlock.
         */
        DenseBlock() : Block<MatrixType>() {}

        /**
         * @brief Constructor with matrix initialization.
         *
         * Initializes the DenseBlock with the given dense matrix.
         *
         * @param matrix The dense matrix to initialize the block with.
         */
        DenseBlock(const MatrixType& matrix) : Block<MatrixType>(matrix) {}

        /**
         * @brief Get the value at the specified position.
         *
         * @param row The row index.
         * @param col The column index.
         * @return The value at the specified position.
         */
        Scalar get(size_t row, size_t col) const override { return this->matrix(row, col); }

        /**
         * @brief Set the value at the specified position.
         *
         * @param row The row index.
         * @param col The column index.
         * @param value The value to set.
         */
        void set(size_t row, size_t col, const Scalar& value) override { this->matrix(row, col) = value; }

        /**
         * @brief Get the type of the block.
         *
         * @return The type of the block, which is BlockTypeEnum::Dense.
         */
        BlockTypeEnum getType() const override { return BlockTypeEnum::Dense; }

        /**
         * @brief Print the dense block matrix.
         *
         * Prints the dense block matrix to the standard output.
         */
        void print() const override {
            std::cout << this->matrix << std::endl;
        }
    };  
}