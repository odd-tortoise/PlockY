#pragma once
#include <iostream>
#include "PlockY/Block.hpp"
#include <vector>
#include <memory>

namespace PlockY {
    template <typename Scalar>
    class BlockMatrix {
        static_assert(std::is_arithmetic<Scalar>::value, "Scalar must be a numeric type");
    public:
        BlockMatrix() = default;

        void setBlock(int row, int col, std::unique_ptr<Block<Scalar>> block) {
            blocks.push_back(std::make_tuple(row, col, std::move(block)));
        }


        std::shared_ptr<Block<Scalar>> getBlock(int row, int col) { 
                for (const auto& block : blocks) {
                    if (std::get<0>(block) == row && std::get<1>(block) == col) {
                        return std::get<2>(block) ;
                    }
                }
                return nullptr;
        }     

        void print() {
            std::cout << "Block length: " << blocks.size() << std::endl;

            for (const auto& blockTuple : blocks) {
                int row = std::get<0>(blockTuple);
                int col = std::get<1>(blockTuple);
                std::shared_ptr<Block<Scalar>> block = std::get<2>(blockTuple);

                std::cout << "Block at (" << row << ", " << col << "): ";
                if (block) {
                    block->print();
                } else {
                    std::cout << "Empty Block" << std::endl;
                }
            }
        }   

    private:
        std::vector<std::tuple<int, int, std::shared_ptr<Block<Scalar>>>> blocks;
    };
}


/*
std::unique_ptr if each Block is owned by exactly one BlockMatrix, or 
std::shared_ptr if blocks can be shared among multiple BlockMatrix instances.
*/

/*
When you return a std::unique_ptr from a function, you're transferring ownership of the object. 
The caller of the function becomes responsible for deleting the object. 
If you were to return a std::unique_ptr from getBlock, the BlockMatrix would no longer be able to access the block,
 because the std::unique_ptr would be moved out of the blocks vector.

If you want to return a smart pointer from getBlock without transferring ownership,
you could use std::shared_ptr instead of std::unique_ptr. With std::shared_ptr,
multiple pointers can share ownership of an object.
However, this comes with some overhead and complexity,
and it's not necessary if the BlockMatrix is the sole owner of the blocks.
*/