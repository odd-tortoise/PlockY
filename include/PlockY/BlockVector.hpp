#pragma once
#include <iostream>
#include "Eigen/Dense"
#include <vector>
#include "PlockY/Strategy.hpp"
#include <memory>
#include <numeric>
#include "PlockY/VecBlock.hpp"

namespace PlockY {
    template <typename BlockType>
    class BlockVector {
    private:
        using MatrixType = typename BlockType::MatrixType;
        static_assert(std::is_base_of<Block<MatrixType>, BlockType>::value, "BlockType must be a subclass of Block");
        
        std::vector<std::tuple<int, std::shared_ptr<BlockType>>> vec_blocks;
        std::vector<MatrixType> RHS;

        MatrixType regroup_indices(std::vector<int> step) const{
            std::vector<MatrixType> res;
            for (const auto& pos : step) {
                auto blockPtr = getBlock(pos);
                if (blockPtr == nullptr) {
                    throw std::runtime_error("Block not found");
                }
                res.push_back(blockPtr->getMatrix());
            }
            return MatrixConcatenator<MatrixType>::concatenateVertically(res);
        }

        bool isValidStrategy(const Strategy& strat) const {
            std::set<int> blockSet;
            for (const auto& block : vec_blocks) {
                blockSet.insert(std::get<0>(block));
            }

            std::vector<int> mergedAndSorted(blockSet.begin(), blockSet.end());
            std::sort(mergedAndSorted.begin(), mergedAndSorted.end());

            return strat.get_merged() == mergedAndSorted;
        }

    public:
        BlockVector() = default;

        void setBlock(int pos, std::unique_ptr<BlockType> block) {
            vec_blocks.push_back(std::make_tuple(pos, std::move(block)));
        }

        std::shared_ptr<BlockType> getBlock(int pos) const {
            for (const auto& block : vec_blocks) {
                if (std::get<0>(block) == pos) {
                    return std::get<1>(block);
                }
            }
            return nullptr;
        }

        void regroup(const Strategy& strategy) {
            if (!isValidStrategy(strategy)){
                throw std::runtime_error("Strategy not valid for the vector");
            }
            RHS.clear();
 
            auto steps = strategy.get_steps();
            for (const auto& step : steps) {
                RHS.push_back( regroup_indices(step.get_block_pos()));
            }
        }

        void print() {
            for (const auto& block : vec_blocks) {
                std::cout << "Position: " << std::get<0>(block) << " Block: " << std::endl;
                std::get<1>(block)->print();
            }
        }


        void update(const Step& step, int i, const MatrixType& u_star) {
            //update the guess
            int start = 0;
            for (const auto& pos : step.get_block_pos()) {
                for (auto& tuple : vec_blocks) {
                    if (std::get<0>(tuple) == pos) {
                        std::get<1>(tuple)->setMatrix((u_star.segment(start, this->getBlock(pos)->getRows())));
                        start += this->getBlock(pos)->getRows();
                    }
                }
            }

            //update the RHS
            RHS[i] = u_star;
        }

        int get_size() const {
            return vec_blocks.size();
        }


        const MatrixType& get_rhs(int i) const {
            return RHS[i];
        }

        const MatrixType get_rhs_compl(const Strategy& strat, int i) const {
            return regroup_indices(strat.get_complementary_blocks(i));
        }


        //utility function to convert the block vector to string for debugging
        std::string to_string() {
            std::string res = "";
            for (const auto& block : vec_blocks) {
                res += vectoString(std::get<1>(block)->getMatrix()) + "\n";
            }
            return res;
        }
        static std::string vectoString(const MatrixType& mat){
            std::stringstream ss;
            ss << mat;
            return ss.str();
        }
    
    };
}