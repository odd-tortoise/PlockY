#pragma once
#include "PlockY/AbstractBlockLoaderFactory.hpp"
#include "PlockY/DenseBlock.hpp"
#include "PlockY/SparseBlock.hpp"

namespace PlockY {

    template <typename Scalar>
    class BinBlockLoader : public AbstractBlockFactory<Scalar> {
    public:
        std::unique_ptr<Block<Scalar>> createDense(const std::string& filePath, int row, int col) override {
            // Open the binary file
            std::ifstream file(filePath, std::ios::binary);
            if (!file) {
                throw std::runtime_error("Could not open file");
            }

            // Read the data into an Eigen matrix
            Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> matrix(row, col);
            file.read(reinterpret_cast<char*>(matrix.data()), sizeof(Scalar) * row * col);

            // Create a DenseBlock and populate it with the matrix data
            auto block = std::make_unique<DenseBlock<Scalar>>(row, col);
            block->setMatrix(matrix);
            return block;
        }

        std::unique_ptr<Block<Scalar>> createSparse(const std::string& filePath, int row, int col) override {
            // Open the binary file
            std::ifstream file(filePath, std::ios::binary);
            if (!file) {
                throw std::runtime_error("Could not open file");
            }

            // Read the triplet list size
            size_t numTriplets;
            file.read(reinterpret_cast<char*>(&numTriplets), sizeof(size_t));

            // Read the triplet list from the binary file
            std::vector<Eigen::Triplet<Scalar>> tripletList(numTriplets);
            file.read(reinterpret_cast<char*>(tripletList.data()), sizeof(Eigen::Triplet<Scalar>) * numTriplets);

            // Create a SparseMatrix and populate it with the triplet list
            Eigen::SparseMatrix<Scalar> mat(row, col);
            mat.setFromTriplets(tripletList.begin(), tripletList.end());

            // Create a SparseBlock and populate it with the matrix data
            auto block = std::make_unique<SparseBlock<Scalar>>(row, col);
            block->setMatrix(mat);
            return block;
        }
    };

}


