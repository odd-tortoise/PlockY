#pragma once
#include "PlockY/BlockMatrix.hpp"
#include "PlockY/BlockVector.hpp"
#include "PlockY/Strategy.hpp"
#include "PlockY/Step.hpp"
#include "PlockY/BlockSolverBase.hpp"
#include <fstream>
#include <optional>
#include <string>

namespace PlockY {


    template <typename BlockType, typename VectorBlockType>
    class Solver {
    private:
        using MatrixType = typename BlockType::MatrixType;
        using VectorType = typename VectorBlockType::MatrixType;

        static_assert(std::is_same<typename MatrixType::Scalar, typename VectorType::Scalar>::value, "Using 2 different scalar type");
        using Scalar = typename MatrixType::Scalar;
       
        static_assert(std::is_base_of<Block<MatrixType>, BlockType>::value, "BlockType must be a subclass of Block");
        static_assert(std::is_base_of<Block<VectorType>, VectorBlockType>::value, "BlockType must be a subclass of Block");
        
        double res = 0;
        bool toll_criteria_not_met = true;
        double toll = 1e-6;
        size_t max_iter = 1000;
        double relax_factor = 0.5;

        std::vector<std::shared_ptr<BlockSolverBase<MatrixType, VectorType>>> block_solvers;
        Strategy strategy;

        VectorType relax(const VectorType& u_star, const VectorType& u_old, double relax_factor) {
            return relax_factor * u_star + (1-relax_factor) * u_old;
        }
        
        double calculate_residual(const BlockVector<VectorBlockType>& u_old, const BlockVector<VectorBlockType>& u_new) {
            double res = 0;
            for (int i = 0; i < strategy.get_steps().size(); i++) {
                res += (u_old.get_rhs(i) - u_new.get_rhs(i)).squaredNorm();
            }
            return std::sqrt(res);
        }
        

    public:

        Solver(double toll, size_t max_iter, double relax, const Strategy& strat, const std::vector<std::shared_ptr<BlockSolverBase<MatrixType, VectorType>>>& block_solvers)
        : toll(toll), max_iter(max_iter), relax_factor(relax), strategy(strat), block_solvers(block_solvers) {
            if (block_solvers.size() != strat.get_steps().size()) {
                throw std::invalid_argument("Size of block_solvers does not match size of steps in strategy");
            }
        }

        Solver(double toll, size_t max_iter, double relax, const Strategy& strat, const std::shared_ptr<BlockSolverBase<MatrixType, VectorType>>& block_solver)
        : toll(toll), max_iter(max_iter), relax_factor(relax), strategy(strat), block_solvers(std::vector<std::shared_ptr<BlockSolverBase<MatrixType, VectorType>>>(strat.get_steps().size(), block_solver)) {}

        BlockVector<VectorBlockType> solve(BlockMatrix<BlockType>& matrix,
                                           BlockVector<VectorBlockType>& rhs,
                                           BlockVector<VectorBlockType>& guess,
                                           const std::optional<std::string>& output_dir = std::nullopt
                                           ) {  
            
            matrix.regroup(strategy);
            rhs.regroup(strategy);
            guess.regroup(strategy);
            
            BlockVector<VectorBlockType> u_old = guess;

            const auto& steps = strategy.get_steps();
            
            while (toll_criteria_not_met and max_iter-- > 0) {
                for(int i=0; i < steps.size(); i++) {
                    const auto& LHS = matrix.get_lhs(i);
                    
                    const auto& u_star_old = guess.get_rhs_compl(strategy,i);
                   
                    auto RHS = rhs.get_rhs(i) - matrix.get_corr(i) * u_star_old;  
                    
                    auto u_star = block_solvers[i]->solveBlock(LHS, RHS);
                  
                    u_star = relax(u_star, u_old.get_rhs(i), relax_factor);    
  
                    guess.update(steps[i], i, u_star);    
                }
                res = calculate_residual(u_old, guess);
                std::cout << "Residual: " << res << std::endl;
                u_old = guess;
                toll_criteria_not_met = res > toll;
            }
            return guess;
        }

    };
}


/*
  if (output_dir) {
                        std::ostringstream filename;
                        filename << *output_dir << "/iter_" << max_iter << "_step_" << i << ".txt";
                        std::ofstream outputFile(filename.str());
                        if (!outputFile.is_open()) {
                            throw std::runtime_error("Cannot open output file");
                        }
                        outputFile << guess.to_string();          
                        outputFile.close();
                    }
*/