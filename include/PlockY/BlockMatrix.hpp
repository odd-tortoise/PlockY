#pragma once
#include <iostream>
#include "PlockY/Block.hpp"
#include <vector>
#include <memory>
#include "PlockY/Step.hpp"
#include "PlockY/DenseBlock.hpp"

namespace PlockY {
    template <typename Scalar>
    class BlockMatrix {
        static_assert(std::is_arithmetic<Scalar>::value, "Scalar must be a numeric type");
    public:
        BlockMatrix() = default;

        void setBlock(int row, int col, std::unique_ptr<Block<Scalar>> block) {
            blocks.push_back(std::make_tuple(row, col, std::move(block)));
        }

        std::shared_ptr<Block<Scalar>> getBlock(int row, int col) const { 
            for (const auto& block : blocks) {
                if (std::get<0>(block) == row && std::get<1>(block) == col) {
                    return std::get<2>(block) ;
                }
            }
            return nullptr;
        }

        void regroup(const std::vector<Step>& steps) {
        //assume that in RHS the positions are all contigous so we can take the max of the position and check if all the steps cover all the blocks.
        // Calculate the maximum position in RHS
        //int maxPosition = rhs.getMaxPosition();

        // Check if all the steps cover all the blocks

        std::vector<int> mergedVector;
        for (const Step& step : steps) {
            mergedVector.insert(mergedVector.end(), step.get_block_pos().begin(), step.get_block_pos().end());
        }

        std::sort(mergedVector.begin(), mergedVector.end());
        /*
        bool allBlocksCovered = true;
        for (int i = 0; i < maxPosition; i++) { //check if the merged vector is equal to the range of the max position, todo
            if (mergedVector[i] != i) {
                allBlocksCovered = false;
                break;
            }
        }
        if (!allBlocksCovered) {
            std::__throw_runtime_error("Not all blocks are covered by the steps");
        }
        */
        //calcuaate LHS
        for (const Step& step : steps) {
            Eigen::MatrixXd lhs_step = Eigen::MatrixXd::Zero(0, 0);
            Eigen::MatrixXd mat_new = Eigen::MatrixXd::Zero(0, 0);
            Eigen::MatrixXd temp = Eigen::MatrixXd::Zero(0, 0);
            Eigen::MatrixXd temp_2 = Eigen::MatrixXd::Zero(0, 0);
            for(int i = 0; i < step.get_block_pos().size(); i++) {
                Eigen::MatrixXd mat = std::dynamic_pointer_cast<DenseBlock<Scalar>>(this->getBlock(step.get_block_pos()[i], step.get_block_pos()[0]))->getMatrix();
                for(int j = 1; j < step.get_block_pos().size(); j++) {
                    mat_new = std::dynamic_pointer_cast<DenseBlock<Scalar>>(this->getBlock(step.get_block_pos()[i], step.get_block_pos()[j]))->getMatrix(); //provvisorio
                    temp.resize(mat.rows(), mat.cols()+mat_new.cols());
                    temp << mat,mat_new;
                    mat = temp;
                }
                if (i==0){
                    lhs_step = mat;
                } else{
                    temp_2.resize(lhs_step.rows()+mat.rows(), lhs_step.cols());
                    temp_2 << lhs_step, mat;
                    lhs_step = temp_2;
                }
            }
            LHS.push_back(lhs_step); 
        }

        for (int i = 0; i < LHS.size(); i++) {
            std::cout << "LHS " << i << std::endl;
            std::cout << LHS[i] << std::endl;
        }

        //calculate RHS
        for(const Step& step : steps) {
            std::vector<int> indices = mergedVector;
            for (const auto& block_pos : step.get_block_pos()) {
                indices.erase(std::remove(indices.begin(), indices.end(), block_pos), indices.end());
            }
            Eigen::MatrixXd lhs_step = Eigen::MatrixXd::Zero(0, 0);
            Eigen::MatrixXd mat_new = Eigen::MatrixXd::Zero(0, 0);
            Eigen::MatrixXd temp = Eigen::MatrixXd::Zero(0, 0);
            Eigen::MatrixXd temp_2 = Eigen::MatrixXd::Zero(0, 0);
            for(int i = 0; i < step.get_block_pos().size(); i++) {
                Eigen::MatrixXd mat = std::dynamic_pointer_cast<DenseBlock<Scalar>>(this->getBlock(step.get_block_pos()[i], indices[0]))->getMatrix();
                for(int j = 1; j < indices.size(); j++) {
                    mat_new = std::dynamic_pointer_cast<DenseBlock<Scalar>>(this->getBlock(step.get_block_pos()[i], indices[j]))->getMatrix(); //provvisorio
                    temp.resize(mat.rows(), mat.cols()+mat_new.cols());
                    temp << mat,mat_new;
                    mat = temp;
                }
                if (i==0){
                    lhs_step = mat;
                } else{
                    temp_2.resize(lhs_step.rows()+mat.rows(), lhs_step.cols());
                    temp_2 << lhs_step, mat;
                    lhs_step = temp_2;
                }
            }
            RHS_mat.push_back(lhs_step); 
        }

        for (int i = 0; i<RHS_mat.size(); i++) {
            std::cout << "RHS " << i << std::endl;
            std::cout << RHS_mat[i] << std::endl;
        }

    }

    Eigen::MatrixXd get_lhs(int i) {
        return LHS[i];
    }

    Eigen::MatrixXd get_rhs(int i) {
        return RHS_mat[i];
    }
        

    private:
        std::vector<std::tuple<int, int, std::shared_ptr<Block<Scalar>>>> blocks;
        std::vector<Eigen::MatrixXd> LHS;
        std::vector<Eigen::MatrixXd> RHS_mat;

    };
}

/*
When you return a std::unique_ptr from a function, you're transferring ownership of the object. 
The caller of the function becomes responsible for deleting the object. 
If you were to return a std::unique_ptr from getBlock, the BlockMatrix would no longer be able to access the block,
 because the std::unique_ptr would be moved out of the blocks vector.

If you want to return a smart pointer from getBlock without transferring ownership,
you could use std::shared_ptr instead of std::unique_ptr. With std::shared_ptr,
multiple pointers can share ownership of an object.
However, this comes with some overhead and complexity,
and it's not necessary if the BlockMatrix is the sole owner of the blocks.
*/