#pragma once

#include "PlockY/Block.hpp"

namespace PlockY
{
    /**
     * @brief A class representing a vector block.
     * 
     * It provides methods to get and set elements in the vector, as well as
     * to print the vector.
     *
     * @tparam Scalar The data type of the elements in the vector.
     */
    template <typename Scalar>
    class VectorBlock : public Block<Eigen::Matrix<Scalar, Eigen::Dynamic, 1>> { 

    public:
        using MatrixType = Eigen::Matrix<Scalar, Eigen::Dynamic, 1>;

        /**
         * @brief Default constructor.
         *
         * Initializes an empty VectorBlock.
         */
        VectorBlock() : Block<MatrixType>() {}

        /**
         * @brief Constructor with matrix initialization.
         *
         * Initializes the VectorBlock with the given vector.
         *
         * @param matrix The vector to initialize the block with.
         */
        VectorBlock(const MatrixType& matrix) : Block<MatrixType>(matrix) {}

        /**
         * @brief Get the value at the specified row.
         *
         * @param row The row index.
         * @return The value at the specified row.
         */
        Scalar get(size_t row) const { return this->matrix(row); }

        /**
         * @brief Set the value at the specified row.
         *
         * @param row The row index.
         * @param value The value to set.
         */
        void set(size_t row, const Scalar& value) { this->matrix(row) = value; }

        /**
         * @brief Get the value at the specified position.
         *
         * @param row The row index.
         * @param col The column index (must be 0).
         * @return The value at the specified position.
         * @throws std::invalid_argument if col is not 0.
         */
        Scalar get(size_t row, size_t col) const override { 
            if (col != 0) {
                throw std::invalid_argument("Column index out of bounds");
            }
            return this->matrix(row, col); 
        }

        /**
         * @brief Set the value at the specified position.
         *
         * @param row The row index.
         * @param col The column index (must be 0).
         * @param value The value to set.
         * @throws std::invalid_argument if col is not 0.
         */
        void set(size_t row, size_t col, const Scalar& value) override { 
            if (col != 0) {
                throw std::invalid_argument("Column index out of bounds");
            }
            this->matrix(row, col) = value; 
        }

        /**
         * @brief Get the type of the block.
         *
         * @return The type of the block, which is BlockTypeEnum::Vec.
         */
        BlockTypeEnum getType() const override { return BlockTypeEnum::Vec; }

        /**
         * @brief Print the vector block.
         *
         * Prints the vector block to the standard output.
         */
        void print() const override {
            std::cout << this->matrix << std::endl;
        }

    };  
}