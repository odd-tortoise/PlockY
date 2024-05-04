#include "PlockY/BlockMatrixLoader.hpp"
#include "PlockY/BlockMatrix.hpp"
#include "PlockY/BlockVectorLoader.hpp"

int main() {

    auto blockMatrix = PlockY::BlockMatrixLoader::load<double>("blk_files/simple_block_mat.blk");
    blockMatrix.print();

    auto blockVector = PlockY::BlockVectorLoader::load<double>("blk_files/simple_block_vect.vblk");
    blockVector.print();
    
    return 0;
} 