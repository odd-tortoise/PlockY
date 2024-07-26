#pragma once
#include "PlockY/AbstractBlockLoaderFactory.hpp"
#include "PlockY/DenseBlock.hpp"
#include "PlockY/SparseBlock.hpp"
#include "PlockY/VecBlock.hpp"


namespace PlockY{
    template <typename Scalar>
    class CsvBlockLoader : public AbstractBlockFactory<Scalar> {
    public:
        std::unique_ptr<DenseBlock<Scalar>> createDense(const std::string& filePath, size_t row, size_t col) override {
            // Open the file
            std::ifstream file(filePath);
            if (!file) {
                throw std::runtime_error("Could not open file: " + filePath);
            }

            // Read the first line to determine the number of columns
            std::string line;
            std::getline(file, line);
            std::stringstream ss(line);
            // Create an Eigen matrix to hold the data
            typename DenseBlock<Scalar>::MatrixType matrix(row, col);

            // Read the data into the matrix

            for (int i = 0; i < row; ++i) {
                ss.clear();
                ss.str(line);
                for (int j = 0; j < col; ++j) {
                    ss >> matrix(i, j);
                    if (ss.peek() == ',') {
                        ss.ignore();
                    }
                }
                std::getline(file, line);
            }

            return std::make_unique<DenseBlock<Scalar>>(matrix);
            
        }

        std::unique_ptr<SparseBlock<Scalar>> createSparse(const std::string& filePath, size_t row, size_t col) override {
            // Open the file
            std::ifstream file(filePath);
            if (!file) {
                throw std::runtime_error("Could not open file: " + filePath);
            }
            // Read the data from the file
            std::string line;
            std::vector<Eigen::Triplet<Scalar>> tripletList;
            while (std::getline(file, line)) {
                std::stringstream ss(line);
                std::string cell;
                std::vector<std::string> cells;

                while (std::getline(ss, cell, ',')) {
                    cells.push_back(cell);
                }

                if (cells.size() == 3) {
                    int i = std::stoi(cells[0]);
                    int j = std::stoi(cells[1]);
                    Scalar value = std::stod(cells[2]); //TODO: fix this as they do here specializing a template CSV line, https://gitlab.com/libeigen/eigen/-/blob/master/unsupported/Eigen/src/SparseExtra/MarketIO.h?ref_type=heads
                    tripletList.push_back(Eigen::Triplet<Scalar>(i, j, value));
                }
            }
            // Create a SparseMatrix and populate it with the triplet list
            typename SparseBlock<Scalar>::MatrixType mat(row, col);
            mat.setFromTriplets(tripletList.begin(), tripletList.end());
            return std::make_unique<SparseBlock<Scalar>>(mat);
        }
    
        std::unique_ptr<VectorBlock<Scalar>> createVector(const std::string& filePath, size_t row) override {
            // Open the file
            std::ifstream file(filePath);
            if (!file) {
                throw std::runtime_error("Could not open file: " + filePath);
            }

            // Read the first line to determine the number of columns
            std::string line;
            std::getline(file, line);
            std::stringstream ss(line);
            // Create an Eigen matrix to hold the data
            typename VectorBlock<Scalar>::MatrixType matrix(row);

            // Read the data into the matrix

            for (int i = 0; i < row; ++i) {
                ss.clear();
                ss.str(line);
                ss >> matrix(i);
                std::getline(file, line);
            }
            return  std::make_unique<VectorBlock<Scalar>>(matrix);
       }
    };
}