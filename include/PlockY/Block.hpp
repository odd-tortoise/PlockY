#pragma once

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <iostream>
#include <variant>  

namespace PlockY {
    /**
     * @brief The Block class is an abstract base class that represents a block of data.
     * 
     * @tparam Scalar The type of data stored in the block.
     */
    enum class BlockType { Dense, Sparse };

    template <typename Scalar>
    class Block {
        static_assert(std::is_arithmetic<Scalar>::value, "Scalar must be a numeric type");
    public:
        /**
         * @brief Default constructor for the Block class.
         */
        Block();

        /**
         * @brief Virtual destructor for the Block class.
         * 
         * This destructor is declared as pure virtual to make the Block class abstract.
         * It ensures that the Block class cannot be instantiated directly.
         */
        virtual ~Block() = 0;

        Block(int rows_, int cols_) : rows(rows_), cols(cols_) {}

        int getRows() const { return rows; }
        int getCols() const { return cols; }

        virtual Scalar get(int row, int col) const = 0;
        virtual void set(int row, int col, const Scalar& value) = 0;

        virtual BlockType getType() const = 0;

    private:
        int rows; /**< The number of rows in the block. */
        int cols; /**< The number of columns in the block. */
    };

    template <typename Scalar>
    Block<Scalar>::~Block() {}
}