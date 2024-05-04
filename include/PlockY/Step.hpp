#pragma once
#include <vector>
#include "Plocky/BlockSolverBase.hpp"
#include <memory>

namespace PlockY {
    class Step {
        private:
            std::vector<int> block_pos;
            std::shared_ptr<BlockSolverBase> solver;
    
        public:

            Step(std::vector<int> block_pos, std::shared_ptr<BlockSolverBase> sol) : block_pos(block_pos), solver(sol) {}
            
            std::shared_ptr<BlockSolverBase> get_solver() const { return solver; }
            
            const std::vector<int>& get_block_pos() const { return block_pos; }
            
            Step(std::vector<int> block_pos) : block_pos(block_pos) {}
    };
}