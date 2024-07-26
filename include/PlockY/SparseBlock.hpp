#pragma once

#include "Block.hpp"

namespace PlockY
{
/**
 * @brief A class representing a sparse block matrix based on Eigen's SparseMatrix type.
 *
 * It provides methods to get and set elements in the sparse matrix, as well as
 * to print the matrix.
 *
 * @tparam Scalar The data type of the elements in the sparse matrix.
 */
template <typename Scalar>
class SparseBlock : public Block<Eigen::SparseMatrix<Scalar>> {
public:
    using MatrixType = Eigen::SparseMatrix<Scalar>;

    /**
     * @brief Default constructor.
     *
     * Initializes an empty SparseBlock.
     */
    SparseBlock() : Block<MatrixType>() {}

    /**
     * @brief Constructor with matrix initialization.
     *
     * Initializes the SparseBlock with the given sparse matrix.
     *
     * @param matrix The sparse matrix to initialize the block with.
     */
    SparseBlock(const MatrixType& matrix) : Block<MatrixType>(matrix) {}

    /**
     * @brief Get the value at the specified position.
     *
     * @param row The row index.
     * @param col The column index.
     * @return The value at the specified position.
     */
    Scalar get(size_t row, size_t col) const override {
        return this->matrix.coeff(row, col);
    }

    /**
     * @brief Set the value at the specified position.
     *
     * @param row The row index.
     * @param col The column index.
     * @param value The value to set.
     */
    void set(size_t row, size_t col, const Scalar& value) override {
        this->matrix.insert(row, col) = value;
    }

    /**
     * @brief Get the type of the block.
     *
     * @return The type of the block, which is BlockTypeEnum::Sparse.
     */
    BlockTypeEnum getType() const override {
        return BlockTypeEnum::Sparse;
    }

    /**
     * @brief Print the sparse block matrix.
     *
     * Prints the sparse block matrix to the standard output.
     */
    void print() const override {
        std::cout << this->matrix << std::endl;
    }
};
}