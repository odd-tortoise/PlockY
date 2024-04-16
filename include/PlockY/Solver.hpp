#pragma once
#include "PlockY/BlockMatrix.hpp"
#include "PlockY/VectorRHS.hpp"
#include "PlockY/Step.hpp"
#include "PlockY/BlockSolverBase.hpp"
#include "PLockY/LUBlockSolver.hpp"

namespace PlockY {

    
    class Solver {
    private:

        double res = 0;
        bool toll_criteria_not_met = true;
        double toll = 1e-6;
        size_t max_iter = 1000;
        LUSolver solverLU;

        Eigen::VectorXd relax(const Eigen::VectorXd& u_star, const Eigen::VectorXd& u_guess, double relax_factor) {
            return relax_factor * u_guess + (1-relax_factor) * (u_star - u_guess);
        }

        double calculate_residual() {
            return 1;
        }

    public:

        Solver (double toll, size_t max_iter) : toll(toll), max_iter(max_iter) {}

        template <typename Scalar>
        VectorRHS<Scalar> solve(BlockMatrix<Scalar>& matrix, VectorRHS<Scalar>& rhs, VectorRHS<Scalar>& guess, std::vector<Step>& strategy) {
        
            matrix.regroup(strategy);
            rhs.regroup(strategy);
            guess.regroup(strategy);

            VectorRHS<Scalar> u_curr = guess;
            
            while (toll_criteria_not_met and max_iter-- > 0) { 
                std::cout<<"==========="<<max_iter<<"==========="<<std::endl;

                for(int i=0; i<strategy.size(); i++) {
                    auto step = strategy[i];
                    auto relax_factor = step.get_relax_factor();
                    
                    auto LHS = matrix.get_lhs(i);
                    auto RHS = rhs.get_rhs(i) - matrix.get_rhs(i) * u_curr.get_rhs_compl(step);
                    
                    auto u_star = solverLU.solve(LHS, RHS);
                    //u_star = relax(u_star, u_curr.get_rhs(i), relax_factor);
                    std::cout<<" step "<<i<<std::endl;
                    /*std::cout<<"LHS "<<LHS<<std::endl;
                    std::cout<<"RHS mat"<< matrix.get_rhs(i)<<std::endl;
                    std::cout<<"RHS vec"<<rhs.get_rhs(i)<<std::endl;
                    std::cout<<"RHS "<<RHS<<std::endl;
                    std::cout<<"u_star "<<u_star<<std::endl;
                    */
                    u_curr.update(step,i, u_star);
                    u_curr.print();
                    std::cout<<"-------------------"<<std::endl;
                }

                res = calculate_residual();
                guess = u_curr;
                
                toll_criteria_not_met = res > toll; 
            }

            return guess;
        }
    };
}
