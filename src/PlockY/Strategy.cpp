#include "PlockY/Strategy.hpp"

namespace PlockY {

    bool Strategy::isValidStepsVector() const {
        return true;
    }

    void Strategy::print() const {
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

    const std::vector<int> Strategy::get_complementary_blocks(const Step& step) const {
        std::vector<int> indices;
        for(int i = 0; i < mergedVector.size(); i++) {
            if(std::find(step.get_block_pos().begin(), step.get_block_pos().end(), mergedVector[i]) == step.get_block_pos().end()){
                indices.push_back(mergedVector[i]);
            }
        }
        return indices;
    }

    Strategy::Strategy(const std::vector<Step>& steps) : steps(steps) {

        //check valididty of the steps
        if (!isValidStepsVector()) {
            throw std::invalid_argument("Invalid steps vector provided.");
        }

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


        //RHS block indices -> block positions X {mergedVector\block positions}
        /*
        for (const Step& step : steps) {
            std::vector<int> indices = mergedVector;
            for (const auto& block_pos : step.get_block_pos()) {
                indices.erase(std::remove(indices.begin(), indices.end(), block_pos), indices.end());
            }
            std::vector<std::tuple<int,int>> indices_tuples;
            for (const auto& block_pos : step.get_block_pos()) {
                for (const auto& index : indices) {
                    indices_tuples.push_back(std::make_tuple(block_pos, index));
                }
            }
            RHS_indices.push_back(indices_tuples);
        }
        */

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

    }

}