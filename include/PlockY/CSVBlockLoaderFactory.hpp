#pragma once
#include "PlockY/AbstractBlockLoaderFactory.hpp"
#include "PlockY/DenseBlock.hpp"
#include "PlockY/SparseBlock.hpp"
#include "PlockY/VecBlock.hpp"


namespace PlockY{
    template <typename Scalar>
    class CsvBlockLoader : public AbstractBlockFactory<Scalar> {
    public:
        std::unique_ptr<DenseBlock<Scalar>> createDense(const std::string& filePath, int row, int col) override {
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
            Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> matrix(row, col);

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

            // Create a DenseBlock and populate it with the matrix data
            auto block = std::make_unique<DenseBlock<Scalar>>(row, col);
            block->setMatrix(matrix);
            return block;
            
        }

        std::unique_ptr<SparseBlock<Scalar>> createSparse(const std::string& filePath, int row, int col) override {
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
            Eigen::SparseMatrix<double> mat;
            mat.setFromTriplets(tripletList.begin(), tripletList.end());
             // Create a SparseBlock and populate it with the matrix data
            auto block = std::make_unique<SparseBlock<Scalar>>(mat.rows(), mat.cols());
            block->setMatrix(mat);
            return block;
        }
    
        std::unique_ptr<VecBlock<Scalar>> createVector(const std::string& filePath, int row) override {
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
            Eigen::Matrix<Scalar, Eigen::Dynamic,1> matrix(row,1);

            // Read the data into the matrix

            for (int i = 0; i < row; ++i) {
                ss.clear();
                ss.str(line);
                ss >> matrix(i, 0);
                std::getline(file, line);
            }

            // Create a DenseBlock and populate it with the matrix data
            auto block = std::make_unique<VecBlock<Scalar>>(row);
            block->setMatrix(matrix);
            return block;
       }
    };
}