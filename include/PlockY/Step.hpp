#pragma once
#include <vector>
#include <stdexcept>
#include <memory>
#include <algorithm>

namespace PlockY {
    class Step {
        private:
            std::vector<int> block_pos;
        public:
            const std::vector<int>& get_block_pos() const { return block_pos; }
            Step(std::vector<int> block_pos) : block_pos(block_pos) {
                for (int i = 0; i < block_pos.size() - 1; i++) {
                    if (block_pos[i] >= block_pos[i + 1]) {
                        throw std::runtime_error("The block positions must be in increasing order.");
                    }
                }
            }
    };
}