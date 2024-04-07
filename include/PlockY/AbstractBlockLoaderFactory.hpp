#pragma once

#include "PlockY/Block.hpp"
#include "PlockY/DenseBlock.hpp"
#include "PlockY/SparseBlock.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <Eigen/Dense>

namespace PlockY {

    template <typename Scalar>
    class AbstractBlockFactory {
    static_assert(std::is_arithmetic<Scalar>::value, "Scalar must be a numeric type");

    public:
        virtual std::unique_ptr<Block<Scalar>> createDense(const std::string& filePath, int row, int col) = 0;
        virtual std::unique_ptr<Block<Scalar>> createSparse(const std::string& filePath, int row, int col) = 0;
    };

}