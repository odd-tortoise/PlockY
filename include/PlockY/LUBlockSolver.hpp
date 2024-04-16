#pragma once
#include "PlockY/BlockSolverBase.hpp"
#include <Eigen/LU>
#include <Eigen/Core>
#include "PlockY/Block.hpp"
#include "PlockY/DenseBlock.hpp"
#include "PlockY/SparseBlock.hpp"


namespace PlockY {
    class LUSolver : public BlockSolverBase {
        using VectorType = Eigen::VectorXd;
        using MatrixType = Eigen::MatrixXd;   
    public:
        VectorType solve(const MatrixType& block, const VectorType& vector) const override {
            Eigen::FullPivLU<MatrixType> lu(block);
            return lu.solve(vector);   
        }
    };
} // namespace PlockY