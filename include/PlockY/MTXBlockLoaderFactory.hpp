#pragma once
#include "PlockY/AbstractBlockLoaderFactory.hpp"
#include "PlockY/DenseBlock.hpp"
#include "PlockY/SparseBlock.hpp"
#include "PlockY/VecBlock.hpp"
#include "unsupported/Eigen/SparseExtra" // For loadMarket function


namespace PlockY{
    template <typename Scalar>
    class MTXBlockLoader : public AbstractBlockFactory<Scalar> {
    public:
        std::unique_ptr<DenseBlock<Scalar>> createDense(const std::string& filePath, size_t row, size_t col) override {
            // Open the file
            std::ifstream file(filePath);
            if (!file) {
                throw std::runtime_error("Could not open file");
            }

            Eigen::MatrixXd matrix;
            Eigen::loadMarketDense(matrix, filePath);

            return std::make_unique<DenseBlock<Scalar>>(matrix);
            
        }

        std::unique_ptr<SparseBlock<Scalar>> createSparse(const std::string& filePath, size_t row, size_t col) override {
            std::ifstream file(filePath);
            if (!file) {
                throw std::runtime_error("Could not open file");
            }

            // Read the Matrix Market banner
            std::string banner;
            std::getline(file, banner);

            // Check the matrix type
            if (banner.find("skew-symmetric") != std::string::npos) {
                // Handle skew-symmetric matrix
                Eigen::SparseMatrix<double> matrix;
                Eigen::loadMarket(matrix, filePath);
                Eigen::SparseMatrix<double> skewSymmMatrix = -matrix.transpose();
                matrix += skewSymmMatrix;
                
                return std::make_unique<SparseBlock<Scalar>>(matrix);
            } else if (banner.find("symmetric") != std::string::npos) {
                // Handle symmetric matrix
                Eigen::SparseMatrix<double> matrix;
                Eigen::loadMarket(matrix, filePath);
                Eigen::SparseMatrix<double> symmMatrix = matrix.selfadjointView<Eigen::Lower>();
                return std::make_unique<SparseBlock<Scalar>>(symmMatrix);
            } else {
                // Handle general matrix
                Eigen::SparseMatrix<double> matrix;
                Eigen::loadMarket(matrix, filePath);
                return std::make_unique<SparseBlock<Scalar>>(matrix);
            }
        }
    
        std::unique_ptr<VectorBlock<Scalar>> createVector(const std::string& filePath, size_t row) override {
            // Open the file
            std::ifstream file(filePath);
            if (!file) {
                throw std::runtime_error("Could not open file");
            }
            Eigen::MatrixXd matrix;
            Eigen::loadMarketDense(matrix, filePath);
            return std::make_unique<VectorBlock<Scalar>>(matrix);
            
       }
    };
}