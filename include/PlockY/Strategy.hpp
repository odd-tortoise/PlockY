/**
 * @file Strategy.hpp
 * @brief Contains the declaration of the Strategy class.
 */

#pragma once

#include <vector>
#include "PlockY/Step.hpp"
#include <iostream>

namespace PlockY {
    /**
     * @class Strategy
     * @brief Represents a strategy for the PlockY game.
     */
    class Strategy {
        private:
            std::vector<Step> steps; /**< The steps in the strategy. */
            std::vector<int> mergedVector; /**< The merged vector of all steps. */
            std::vector<std::vector<std::vector<std::tuple<int,int>>>> LHS_indices; /**< The indices of the left-hand side blocks for each step. */
            std::vector<std::vector<std::vector<std::tuple<int,int>>>> RHS_indices; /**< The indices of the right-hand side blocks for each step. */
            std::vector<std::vector<int>> complementary; /**< The complementary blocks for each step. */
        public:
            /**
             * @brief Constructs a Strategy object with the given steps.
             * @param steps The steps in the strategy.
             */
            
   Strategy(const std::vector<Step>& steps) : steps(steps) {
        //merge all the block positions
        for (const Step& step : steps) {
            mergedVector.insert(mergedVector.end(), step.get_block_pos().begin(), step.get_block_pos().end());
        }
        std::sort(mergedVector.begin(), mergedVector.end());


        // LHS blocks indices -> cartesian product of block positions "squared"
        for (const Step& step : steps) {
            std::vector<std::vector<std::tuple<int,int>>> indices;
            for (int i = 0; i < step.get_block_pos().size(); i++) {
                std::vector<std::tuple<int,int>> row;
                for (int j = 0; j < step.get_block_pos().size(); j++) {
                    row.push_back(std::make_tuple(step.get_block_pos()[i], step.get_block_pos()[j]));
                }
                indices.push_back(row);
            }
            LHS_indices.push_back(indices);
        }

        for (const Step& step : steps) {
            std::vector<int> indices = mergedVector;
            std::vector<std::vector<std::tuple<int,int>>> indices_tuples;
            for (const auto& block_pos : step.get_block_pos()) {
                std::vector<std::tuple<int,int>> row;
                for (const auto& index : indices) {
                    if (std::find(step.get_block_pos().begin(), step.get_block_pos().end(), index) == step.get_block_pos().end()) {
                        row.push_back(std::make_tuple(block_pos, index));
                    }
                }
                indices_tuples.push_back(row);
            }
            RHS_indices.push_back(indices_tuples);
        }

        for (const Step& step : steps) {
            complementary.push_back(complementary_blocks(step));
        }

    }

            /**
             * @brief Gets the steps in the strategy.
             * @return The steps in the strategy.
             */
            const std::vector<Step>& get_steps() const { return steps; }

            const std::vector<int>& get_merged() const { return mergedVector; }

            const std::vector<int>& get_complementary_blocks(int i) const { return complementary[i]; }

            /**
             * @brief Prints the strategy.
             */
            
    void print() const {
        /*
        for (const Step& step : steps) {
            std::cout << "Step with blocks: ";
            for (const auto& block : step.get_block_pos()) {
                std::cout << block << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "Merged vector: ";
        for (const auto& block : mergedVector) {
            std::cout << block << " ";
        }
        std::cout << std::endl;
        */

        std::cout<< "LHS indices: " << std::endl;
        for (const auto& indices : LHS_indices) {
            for (const auto& row : indices) {
                for (const auto& index : row) {
                    std::cout << "(" << std::get<0>(index) << ", " << std::get<1>(index) << ") ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        std::cout << "RHS indices: " << std::endl;
        for (const auto& indices : RHS_indices) {
            for (const auto& row : indices) {
                for (const auto& index : row) {
                    std::cout << "(" << std::get<0>(index) << ", " << std::get<1>(index) << ") ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }

    


            /**
             * @brief Gets the indices of the left-hand side blocks for each step.
             * @return The indices of the left-hand side blocks for each step.
             */
            const std::vector<std::vector<std::vector<std::tuple<int,int>>>>& get_LHS_indices() const { return LHS_indices; }

            /**
             * @brief Gets the indices of the right-hand side blocks for each step.
             * @return The indices of the right-hand side blocks for each step.
             */
            const std::vector<std::vector<std::vector<std::tuple<int,int>>>>& get_RHS_indices() const { return RHS_indices; }

            /**
             * @brief Gets the complementary blocks for a given step.
             * @param step The step for which to get the complementary blocks.
             * @return The complementary blocks for the given step.
             */
            const std::vector<int> complementary_blocks(const Step& step) const {
        std::vector<int> indices;
        for(int i = 0; i < mergedVector.size(); i++) {
            if(std::find(step.get_block_pos().begin(), step.get_block_pos().end(), mergedVector[i]) == step.get_block_pos().end()){
                indices.push_back(mergedVector[i]);
            }
        }
        return indices;
    }
    };
}