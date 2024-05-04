#pragma once
#include "PlockY/BlockMatrix.hpp"
#include "PlockY/BlockVector.hpp"
#include "PlockY/Strategy.hpp"
#include "PlockY/Step.hpp"
#include <fstream>

namespace PlockY {

    
    class Solver {
    private:
        double res = 0;
        bool toll_criteria_not_met = true;
        double toll = 1e-6;
        size_t max_iter = 1000;
        double relax_factor = 0.5;

        Eigen::VectorXd relax(const Eigen::VectorXd& u_star, const Eigen::VectorXd& u_guess, double relax_factor) {
            return relax_factor * u_guess + (1-relax_factor) * (u_star - u_guess);
        }

        double calculate_residual() {
            return 1;
        }

    public:

        Solver (double toll, size_t max_iter, double relax) : toll(toll), max_iter(max_iter), relax_factor(relax) {}

        template <typename Scalar>
        BlockVector<Scalar> solve(BlockMatrix<Scalar>& matrix, BlockVector<Scalar>& rhs, BlockVector<Scalar>& guess, const Strategy& strategy) {

            matrix.regroup(strategy);
            rhs.regroup(strategy);
            guess.regroup(strategy);
            std::vector<Step> steps = strategy.get_steps();

      
    
            while (toll_criteria_not_met and max_iter-- > 0) { 

                std::cout<<"==========="<<max_iter<<"==========="<<std::endl;
                //outputFile << " ================= ITER: " << max_iter << " ===================== "<< std::endl;
                for(int i=0; i < steps.size(); i++) {
                    //outputFile << "Step: " << i << std::endl;
                    std::ofstream outputFile("output/iter_"+std::to_string(max_iter) + "_step_"+std::to_string(i)+".txt");
                    if (!outputFile.is_open()) {
                        throw std::runtime_error("Cannot open output file");
                    }
                    auto step = steps[i];
                    auto LHS = matrix.get_lhs(i);
                    auto RHS = rhs.get_rhs(i) - matrix.get_corr(i) * guess.get_rhs_compl(strategy, step);              
                    auto u_star = step.get_solver()->solve(LHS, RHS);
                    guess.update(step, i, u_star); 
                    outputFile << guess.to_string();          
                    outputFile.close();
                    //outputFile << " --------------------------- " << std::endl;  
                }
                res = calculate_residual();
                toll_criteria_not_met = res > toll; 
            }

            return guess;
        }
    };
}