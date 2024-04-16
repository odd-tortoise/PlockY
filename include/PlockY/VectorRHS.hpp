#pragma once
#include <iostream>
#include "Eigen/Dense"
#include <vector>
#include "PlockY/Step.hpp"
#include <memory>
#include <numeric>

namespace PlockY {
    template <typename Scalar>
    class VectorRHS {
        static_assert(std::is_arithmetic<Scalar>::value, "Scalar must be a numeric type");
    private:
        std::vector<std::tuple<int, std::shared_ptr<Eigen::VectorXd>>> vector_blocks;
        std::vector<Eigen::VectorXd> RHS;

        int maxPosition(){
            int max = 0;
            for(const auto& block : vector_blocks) {
                if(std::get<0>(block) > max) {
                    max = std::get<0>(block);
                }
            }
            return max;
        }

    public:
        VectorRHS() = default;

        VectorRHS(const std::vector<Eigen::VectorXd>& rhs) {
            for(int i= 0; i < rhs.size(); i++) {
                vector_blocks.push_back(std::make_tuple(i, std::make_shared<Eigen::VectorXd>(rhs[i])));
            }
        }

        void setBlock(int pos, std::shared_ptr<Eigen::VectorXd> block) {
            vector_blocks.push_back(std::make_tuple(pos, block));
        }

        std::shared_ptr<Eigen::VectorXd> getBlock(int pos) {
            for (const auto& block : vector_blocks) {
                if (std::get<0>(block) == pos) {
                    return std::get<1>(block);
                }
            }
            return nullptr;
        }

        void regroup(const std::vector<Step>& steps) {
            //assume that in RHS the positions are all contigous so we can take the max of the position and check if all the steps cover all the blocks.
            // Calculate the maximum position in RHS
            for(const auto& step : steps) {
                Eigen::VectorXd rhs_step = *this->getBlock(step.get_block_pos()[0]);
                Eigen::VectorXd temp = Eigen::VectorXd::Zero(0);
                Eigen::VectorXd newblock = Eigen::VectorXd::Zero(0);
                
                for(int i = 1; i < step.get_block_pos().size(); i++) {
                    newblock = *this->getBlock(step.get_block_pos()[i]);
                    temp.resize(rhs_step.size() + newblock.size());
                    temp << rhs_step, newblock;
                    rhs_step = temp;
                }
                RHS.push_back(rhs_step);
            }
        
            for(int i = 0; i < RHS.size(); i++) {
                std::cout << "RHS " << i <<std::endl<< RHS[i] << std::endl;
            }

        }


        Eigen::VectorXd get_rhs(int i) {
            return RHS[i];
        }

        std::vector<Eigen::VectorXd> getRHS() {
            return RHS;
        }

        Eigen::VectorXd get_rhs_compl(const Step& step) {

            int max = maxPosition();
            
            std::vector<int> indices;
            for(int i = 0; i < max+1; i++) {
                if(std::find(step.get_block_pos().begin(), step.get_block_pos().end(), i) == step.get_block_pos().end()){
                    indices.push_back(i);
                }
            }

            Eigen::VectorXd rhs_compl = *this->getBlock(indices[0]);
            Eigen::VectorXd temp = Eigen::VectorXd::Zero(0);
            Eigen::VectorXd newblock = Eigen::VectorXd::Zero(0);
            for(int i = 1; i < indices.size(); i++) {
                newblock = *this->getBlock(indices[i]);
                temp.resize(rhs_compl.size() + newblock.size());
                temp << rhs_compl, newblock;
                rhs_compl = temp;
            }

            return rhs_compl;
        }

        VectorRHS& operator=(const VectorRHS& other) {
            if (this == &other) {
                return *this;
            }
            
            vector_blocks = other.vector_blocks;
            RHS = other.RHS;
            
            return *this;
        }

        void print() {
            for (auto tuple : vector_blocks) {
                std::cout << *std::get<1>(tuple) << std::endl;
            }
        }

        void update(Step step,int i, Eigen::VectorXd& u_star) {
            int start = 0;
            for (int j = 0; j < step.get_block_pos().size(); j++) {
                int pos = step.get_block_pos()[j];
               
                for (auto& tuple : vector_blocks) {
                    if (std::get<0>(tuple) == pos) {
                        std::get<1>(tuple) =  std::make_shared<Eigen::VectorXd>(u_star.segment(start, this->getBlock(pos)->size()));
                        start += this->getBlock(pos)->size();
                    }
                }
            }
            RHS[i] = u_star;
        }


    };
}