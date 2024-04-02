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
    public:
        virtual ~AbstractBlockFactory() {}
        // ha senso fare cos?
        virtual std::unique_ptr<DenseBlock<Scalar>> createDense(const std::string& filePath, int row, int col) = 0;
        virtual std::unique_ptr<SparseBlock<Scalar>> createSparse(const std::string& filePath, int row, int col) = 0;
    };
}