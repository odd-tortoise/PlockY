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
     * @todo It would be nice to build a concept for a MatrixType to guide users of the library.
     */

    template <typename MatrixType>
    class Block{
    public:
        /**
         * @brief Default constructor for the Block class.
         * @note Not needed the sintetic constructor is enough
         */
        Block() : matrix(MatrixType()){};


        /**
         * @brief Constructs a Block object with the given matrix.
         *
         * This constructor initializes the Block object by copying the provided matrix.
         * It also sets the git@github.com:google/googletest.gitnumber of rows and columns of the Block based on the provided matrix.
         *
         * @param matrix The matrix to initialize the Block with. The matrix type must have
         *               `rows()` and `cols()` methods to get the number of rows and columns.
         * 
         * @note Not clear to me why you need to store rows and cols as member variables, you can always get them from the matrix.
         * duplicating variables can lead to inconsistencies.
         */
        Block(const MatrixType &matrix) : matrix(matrix){
            rows = matrix.rows();
            cols = matrix.cols();
        }; 

        // at this point I would have added also for competeness the move operators, that at the moment are
        // not provided as you defined a copy constructor and a copy assignment operator
        // Block(Block &&) = default;
        // Block& operator=(Block &&) = default;

        /**
         * @brief Virtual destructor for the Block class.
         *
         * This destructor is declared as pure virtual to make the Block class abstract.
         * It ensures that the Block class cannot be instantiated directly.
         */
        // you already have the method print that is pure virtual and so it makes this class abstract, 
        // so you can define the destructor in the class definition
        // virtual ~Block() = default;
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
        MatrixType matrix; // I would give a default value of MatrixType{} here
        size_t rows; // I would give a default value of 0
        size_t cols;
    };

//@note why do you need this? you can define the destructor in the class definition
    template <typename MatrixType>
    Block<MatrixType>::~Block() = default;
}