#pragma once

#include <Eigen/Dense>
#include <Eigen/Sparse>


namespace PlockY {

template <typename MatrixType, typename VectorType>
class BlockSolverBase {
public:
    virtual VectorType solveBlock(const MatrixType& matrix, const VectorType& vector) = 0;
};

// Specialization for dense matrices
template <typename Scalar>
class EigenDenseLU : public BlockSolverBase<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>, Eigen::Matrix<Scalar, Eigen::Dynamic, 1>> {
public:
    Eigen::Matrix<Scalar, Eigen::Dynamic, 1> solveBlock(const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>& matrix, const Eigen::Matrix<Scalar, Eigen::Dynamic, 1>& vector) override {
        Eigen::FullPivLU<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>> lu(matrix);
        return lu.solve(vector);
    }
};

// Specialization for sparse matrices
template <typename Scalar>
class EigenSparseLU : public BlockSolverBase<Eigen::SparseMatrix<Scalar>, Eigen::Matrix<Scalar, Eigen::Dynamic, 1>> {
public:
    Eigen::Matrix<Scalar, Eigen::Dynamic, 1> solveBlock(const Eigen::SparseMatrix<Scalar>& matrix, const Eigen::Matrix<Scalar, Eigen::Dynamic, 1>& vector) override {
        Eigen::SparseLU<Eigen::SparseMatrix<Scalar>> lu(matrix);
        return lu.solve(vector);
    }
};


}  // namespace PlockY