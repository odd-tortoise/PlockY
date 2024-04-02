#pragma once
#include "PlockY/Block.hpp"

#include <vector>
#include <memory>
#include <variant>

namespace PlockY {
    

    template <typename Scalar>
    class BlockMatrix {
// std::unique_ptr<std::variant<BlockDense, BlockSparse>> ptrVariant;
// oppure
// std::variant<std::shared_ptr<DenseBlock<Scalar>>, std::shared_ptr<SparseBlock<Scalar>>>;

    using BlockPtr = std::variant<std::shared_ptr<DenseBlock<Scalar>>, std::shared_ptr<SparseBlock<Scalar>>>;
    
    public:
        BlockMatrix() = default;

        void setBlock(int row, int col, BlockPtr block) {
            blocks.push_back(std::make_tuple(row, col, std::move(block)));
        }

        BlockPtr getBlock(int row, int col) {
            for (const auto& block : blocks) {
                if (std::get<0>(block) == row && std::get<1>(block) == col) {
                    //devo usare visit ??
                    return std::get<2>(block);   
                }
            }
            return nullptr;
        }

    private:
        std::vector<std::tuple<int, int, BlockPtr>> blocks;
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