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
            Strategy(const std::vector<Step>& steps);

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
            void print() const;

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
            const std::vector<int> complementary_blocks(const Step& step) const; 
    };
}