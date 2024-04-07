#pragma once
#include "PlockY/AbstractBlockLoaderFactory.hpp"
#include "PlockY/DenseBlock.hpp"
#include "PlockY/SparseBlock.hpp"

namespace PlockY{

    
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
                std::cout<<"roww:"<<roww<<" coll:"<<coll<<" value:"<<value<<std::endl;
            }

            // Create a SparseMatrix and populate it with the triplet list
            Eigen::SparseMatrix<double> mat;
            mat.setFromTriplets(tripletList.begin(), tripletList.end());
             // Create a SparseBlock and populate it with the matrix data
            auto block = std::make_unique<SparseBlock<Scalar>>(mat.rows(), mat.cols());
            block->setMatrix(mat);
            return block;
        }
    };

}