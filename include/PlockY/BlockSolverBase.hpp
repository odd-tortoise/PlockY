#pragma once
#include <Eigen/Core>

namespace PlockY {
    class BlockSolverBase {
    public:
        BlockSolverBase() = default;
        virtual ~BlockSolverBase() = default;
        virtual Eigen::Matrix<double, Eigen::Dynamic, 1> solve(const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& block, const Eigen::Matrix<double, Eigen::Dynamic, 1>& vector) const = 0;
    };
}