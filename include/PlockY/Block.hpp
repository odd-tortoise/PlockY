#pragma once

#include <type_traits>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <iostream>
#include <stdexcept>

namespace PlockY
{

    /// @brief Enum class to represent the type of block.
    enum class BlockTypeEnum
    {
        Dense,
        Sparse,
        Vec
    };

    /**
     * @brief Abstract class for a block of data.
     * 
     * This class is a template class that represents a block of data. It is an abstract class, and is intended to be used as a base class for more specific block types.
     * 
     */

    template <typename MatrixType>
    class Block{
    public:
        /**
         * @brief Default constructor for the Block class.
         */
        Block() : matrix(MatrixType()){};


        /**
         * @brief Constructs a Block object with the given matrix.
         *
         * This constructor initializes the Block object by copying the provided matrix.
         * It also sets the number of rows and columns of the Block based on the provided matrix.
         *
         * @param matrix The matrix to initialize the Block with. The matrix type must have
         *               `rows()` and `cols()` methods to get the number of rows and columns.
         */
        Block(const MatrixType &matrix) : matrix(matrix){
            rows = matrix.rows();
            cols = matrix.cols();
        }; 

        /**
         * @brief Virtual destructor for the Block class.
         *
         * This destructor is declared as pure virtual to make the Block class abstract.
         * It ensures that the Block class cannot be instantiated directly.
         */
        virtual ~Block() = 0;

        const size_t getCols() const { return cols; };
        const size_t getRows() const { return rows; };

        virtual typename MatrixType::Scalar get(size_t row, size_t col) const = 0;
        virtual void set(size_t row, size_t col, const typename MatrixType::Scalar &value) = 0;

        virtual BlockTypeEnum getType() const = 0;

        const MatrixType& getMatrix() const {
            return matrix; 
        };

        void setMatrix(const MatrixType &newData){
            if (newData.rows() != rows || newData.cols() != cols){
                throw std::invalid_argument("Size of new data does not match the current size of this block");
            }
            this->matrix = newData;
        };

        virtual void print() const = 0;

    protected:
        MatrixType matrix;
        size_t rows;
        size_t cols;
    };

    template <typename MatrixType>
    Block<MatrixType>::~Block() = default;
}