#pragma once

#include <type_traits>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <iostream>
#include <stdexcept>
#include <concepts>

namespace PlockY
{
    /// @brief Concept to ensure MatrixType has necessary member functions.
    /// @todo make this better
    template <typename T>
    concept MatrixTypeConcept = requires(T a) {
        { a.rows() } -> std::convertible_to<size_t>;
        { a.cols() } -> std::convertible_to<size_t>;
        { a = a } -> std::same_as<T&>;
    };

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

    template <MatrixTypeConcept MatrixType>
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


        // Copy constructor
        Block(const Block& other) : matrix(other.matrix), rows(other.rows), cols(other.cols) {} 

        // Copy assignment operator
        Block& operator=(const Block& other) {
            if (this != &other) {
                matrix = other.matrix;
                rows = other.rows;
                cols = other.cols;
            }
            return *this;
        }

        
        Block(Block&& other) : matrix(std::move(other.matrix)), rows(other.rows), cols(other.cols) {}
               
        Block& operator=(Block&& other) {
            if (this != &other) {
                matrix = std::move(other.matrix);
                rows = other.rows;
                cols = other.cols;
            }
            return *this;
        }

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
        MatrixType matrix = MatrixType{};
        size_t rows = 0;
        size_t cols = 0;
    };

    template <MatrixTypeConcept MatrixType>
    Block<MatrixType>::~Block() = default;
}