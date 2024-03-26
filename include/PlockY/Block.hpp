#pragma once

#include <Eigen/Dense>
#include <Eigen/Sparse>

namespace PlockY {
    /**
     * @brief The Block class is an abstract base class that represents a block of data.
     * 
     * @tparam Scalar The type of data stored in the block.
     */
    template <typename Scalar>
    class Block {
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

        /**
         * @brief Constructor for the Block class.
         * 
         * @param rows_ The number of rows in the block.
         * @param cols_ The number of columns in the block.
         */
        Block(int rows_, int cols_) : rows(rows_), cols(cols_) {}

        /**
         * @brief Get the number of rows in the block.
         * 
         * @return The number of rows in the block.
         */
        int getRows() const { return rows; }

        /**
         * @brief Get the number of columns in the block.
         * 
         * @return The number of columns in the block.
         */
        int getCols() const { return cols; }

        /**
         * @brief Pure virtual method to get the value at a specific position in the block.
         * 
         * @param row The row index.
         * @param col The column index.
         * @return The value at the specified position.
         */
        virtual Scalar get(int row, int col) const = 0;

        /**
         * @brief Pure virtual method to set the value at a specific position in the block.
         * 
         * @param row The row index.
         * @param col The column index.
         * @param value The value to be set.
         */
        virtual void set(int row, int col, const Scalar& value) = 0;
        

        private:
            int rows; /**< The number of rows in the block. */
            int cols; /**< The number of columns in the block. */

        };

        template <typename scalar>
        Block<scalar>::~Block() {}

    }
