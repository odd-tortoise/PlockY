#pragma once
#include "PlockY/BlockSolverBase.hpp"
#include <Eigen/LU>
namespace PlockY {
    class LUSolver : public BlockSolverBase{
    public:
        Eigen::Matrix<double, Eigen::Dynamic, 1> solve(const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& block, const Eigen::Matrix<double, Eigen::Dynamic, 1>& vector) const {
            Eigen::FullPivLU<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>> lu(block);
            return lu.solve(vector);   
        }
    };
} // namespace PlockY