#pragma once

#include "PlockY/Block.hpp"
#include "PlockY/DenseBlock.hpp"
#include "PlockY/SparseBlock.hpp"
#include "PlockY/VecBlock.hpp"
#include <string>
#include <memory>
#include <type_traits>
#include <stdexcept>
#include <fstream>
#include <sstream>

namespace PlockY {

    /**
     * @brief Abstract factory class for creating different types of blocks.
     * 
     * This class provides an interface for creating DenseBlock, SparseBlock, and VectorBlock
     * objects. The Scalar type must be a numeric type.
     * 
     * @tparam Scalar The numeric type used in the blocks.
     */
    template <typename Scalar>
    class AbstractBlockFactory {
        static_assert(std::is_arithmetic<Scalar>::value, "Scalar must be a numeric type");

    public:
        /**
         * @brief Creates a DenseBlock object.
         * 
         * @param filePath The path to the file containing the block data.
         * @param row The number of rows in the block.
         * @param col The number of columns in the block.
         * @return A unique pointer to the created DenseBlock object.
         */
        virtual std::unique_ptr<DenseBlock<Scalar>> createDense(const std::string& filePath, size_t row, size_t col) = 0;

        /**
         * @brief Creates a SparseBlock object.
         * 
         * @param filePath The path to the file containing the block data.
         * @param row The number of rows in the block.
         * @param col The number of columns in the block.
         * @return A unique pointer to the created SparseBlock object.
         */
        virtual std::unique_ptr<SparseBlock<Scalar>> createSparse(const std::string& filePath, size_t row, size_t col) = 0;

        /**
         * @brief Creates a VectorBlock object.
         * 
         * @param filePath The path to the file containing the block data.
         * @param row The number of rows in the block.
         * @return A unique pointer to the created VectorBlock object.
         */
        virtual std::unique_ptr<VectorBlock<Scalar>> createVector(const std::string& filePath, size_t row) = 0;

        /**
         * @brief Virtual destructor for the AbstractBlockFactory class.
         */
        virtual ~AbstractBlockFactory() = default;
    };
}