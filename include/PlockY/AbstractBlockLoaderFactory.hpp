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
    template <typename Scalar>
    class AbstractBlockFactory {
        static_assert(std::is_arithmetic<Scalar>::value, "Scalar must be a numeric type");
    public:
        virtual std::unique_ptr<DenseBlock<Scalar>> createDense(const std::string& filePath, size_t row, size_t col) = 0;
        virtual std::unique_ptr<SparseBlock<Scalar>> createSparse(const std::string& filePath, size_t row, size_t col) = 0;
        virtual std::unique_ptr<VecBlock<Scalar>> createVector(const std::string& filePath, size_t row) = 0;

        virtual ~AbstractBlockFactory() = default;
    };
}