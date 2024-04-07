#pragma once
#include "PlockY/BlockSolverBase.hpp"
#include <Eigen/LU>
#include <Eigen/Core>
#include "PlockY/Block.hpp"
#include "PlockY/DenseBlock.hpp"
#include "PlockY/SparseBlock.hpp"


namespace PlockY {
    template<typename BlockType,typename Scalar>
    class LUSolver : public BlockSolverBase<BlockType> {
    public:
        using VectorType = Eigen::VectorXd;
        VectorType solve(const BlockType& block, const VectorType& vector) const override {
            if (is_instance_of_v<BlockType, DenseBlock>) {
                Eigen::FullPivLU<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>> lu(block.getMatrix());
                return lu.solve(vector);
            } else if  (is_instance_of_v<BlockType, SparseBlock>)  {
                throw std::invalid_argument("Unsupported  SPARSE block type");
            } else {
                throw std::invalid_argument("Unsupported block type");
            }
        }
    };

} // namespace PlockY

