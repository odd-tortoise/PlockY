#pragma once

#include <type_traits>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <iostream>
namespace PlockY
{

    /**
     * @brief The Block class is an abstract base class that represents a block of data.
     *
     * @tparam Scalar The type of data stored in the block.
     */
    enum class BlockTypeEnum
    {
        Dense,
        Sparse,
        Vec
    };

    template <typename MatrixType>
    class Block
    {
    public:
        /**
         * @brief Default constructor for the Block class.
         */
        Block() : matrix(MatrixType()){};
        Block(size_t rows, size_t cols) : rows(rows), cols(cols), matrix(MatrixType()){};
        Block(const MatrixType &matrix) : matrix(matrix){
            rows = matrix.rows();
            cols = matrix.cols();
        }; // assume that matrix type has rows() and cols()

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
            std::cout<<"sto usando il getMatrix base"<<std::endl;
            return matrix; 
        };

        virtual MatrixType getMatrixTransposed() const {
            return getMatrix().transpose();
        }

        void setMatrix(const MatrixType &newData){
            if (newData.rows() != rows || newData.cols() != cols)
            {
                throw std::invalid_argument("Size of new data does not match size of block");
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