#pragma once
#include <vector>
#include "Plocky/BlockSolverBase.hpp"
#include <memory>

namespace PlockY {
    class Step {
        private:
            std::vector<int> block_pos;
            //BlockSolverBase solver;
            double relax_factor;     
     
        public:
            Step(std::vector<int> block_pos, double relax_factor) : block_pos(block_pos),  relax_factor(relax_factor) {}
            const std::vector<int>& get_block_pos() const { return block_pos; }
            //BlockSolverBase get_solver() const { return solver; }
            double get_relax_factor() const { return relax_factor; }
    };
}