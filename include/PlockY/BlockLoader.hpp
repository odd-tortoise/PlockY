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
        virtual std::unique_ptr<Block<Scalar>> createDense(const std::string& filePath, int row, int col) = 0;
        virtual std::unique_ptr<Block<Scalar>> createSparse(const std::string& filePath, int row, int col) = 0;
    };

    template <typename Scalar>
    class CsvBlockLoader : public AbstractBlockFactory<Scalar> {
    public:
        std::unique_ptr<Block<Scalar>> createDense(const std::string& filePath, int row, int col) override {
            // Open the file
            std::ifstream file(filePath);
            if (!file) {
                throw std::runtime_error("Could not open file");
            }

            // Read the first line to determine the number of columns
            std::string line;
            std::getline(file, line);
            std::stringstream ss(line);
            Scalar value;
            int cols = 0;
            while (ss >> value) {
                ++cols;
                if (ss.peek() == ',') {
                    ss.ignore();
                }
            }

            // Create an Eigen matrix to hold the data
            Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> matrix(row, cols);

            // Read the data into the matrix
            ss.clear();
            ss.str(line);
            for (int j = 0; j < cols; ++j) {
                ss >> matrix(0, j);
                if (ss.peek() == ',') {
                    ss.ignore();
                }
            }
            for (int i = 1; i < row; ++i) {
                std::getline(file, line);
                ss.clear();
                ss.str(line);
                for (int j = 0; j < cols; ++j) {
                    ss >> matrix(i, j);
                    if (ss.peek() == ',') {
                        ss.ignore();
                    }
                }
            }

            // Create a DenseBlock and populate it with the matrix data
            auto block = std::make_unique<DenseBlock<Scalar>>(row, cols);
            block->setMatrix(matrix);
            return block;
            
        }

        std::unique_ptr<Block<Scalar>> createSparse(const std::string& filePath, int row, int col) override {
            return std::make_unique<DenseBlock<Scalar>>(row, col);
        }
    };

    template <typename Scalar>
    class JSONBlockLoader : public AbstractBlockFactory<Scalar> {
    public:
        std::unique_ptr<Block<Scalar>> createDense(const std::string& filePath, int row, int col) override {
            return std::make_unique<DenseBlock<Scalar>>(row, col);
        }

        std::unique_ptr<Block<Scalar>> createSparse(const std::string& filePath, int row, int col) override {
            return std::make_unique<DenseBlock<Scalar>>(row, col);
        }
    };

}