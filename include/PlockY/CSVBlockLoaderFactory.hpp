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
                throw std::runtime_error("Could not open file");
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
                throw std::runtime_error("Could not open file");
            }
            // Read the data from the file
            std::string line;
            int roww, coll;
            Scalar value;
            std::vector<Eigen::Triplet<Scalar>> tripletList;
            std::istringstream iss(line);
            while (std::getline(iss, line)) {
                std::istringstream lineStream(line);
                std::string cell;
                std::vector<std::string> cells;

                while (std::getline(lineStream, cell, ',')) {
                    cells.push_back(cell);
                }

                if (cells.size() == 3) {
                    int val1 = std::stoi(cells[0]);
                    int val2 = std::stoi(cells[1]);
                    double val3 = std::stod(cells[2]);
                }
                // Subtract 1 from row and col if your CSV file uses 1-based indexing
                tripletList.push_back(Eigen::Triplet<Scalar>(roww, coll, value));
            }

            // Create a SparseMatrix and populate it with the triplet list
            typename SparseBlock<Scalar>::MatrixType mat;
            mat.setFromTriplets(tripletList.begin(), tripletList.end());
            return std::make_unique<SparseBlock<Scalar>>(mat);
        }
    
        std::unique_ptr<VecBlock<Scalar>> createVector(const std::string& filePath, size_t row) override {
            // Open the file
            std::ifstream file(filePath);
            if (!file) {
                throw std::runtime_error("Could not open file");
            }

            // Read the first line to determine the number of columns
            std::string line;
            std::getline(file, line);
            std::stringstream ss(line);
            // Create an Eigen matrix to hold the data
            typename VecBlock<Scalar>::MatrixType matrix(row);

            // Read the data into the matrix

            for (int i = 0; i < row; ++i) {
                ss.clear();
                ss.str(line);
                ss >> matrix(i);
                std::getline(file, line);
            }
            return  std::make_unique<VecBlock<Scalar>>(matrix);
       }
    };
}