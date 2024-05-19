#include "PlockY.hpp"
#include <iostream>

int main() {
    std::cout<< "Loading a dense block matrix from a .blk file" << std::endl;
    auto blockMatrix_dense = PlockY::BlockMatrixLoader::load<PlockY::DenseBlock<double>>("../data/blk_files/5b5_withNonSquareBlocks_dense.blk");
    blockMatrix_dense.print();

    std::cout << std:: endl;

    std::cout<< "Loading a sparse block matrix from a .blk file" << std::endl;
    auto blockMatrix_sparse = PlockY::BlockMatrixLoader::load<PlockY::SparseBlock<double>>("../data/blk_files/5b5_withNonSquareBlocks_sparse.blk");
    blockMatrix_sparse.print();
    
    std::cout << std:: endl;

    std::cout<< "Loading a block vector from a .vblk file" << std::endl;
    auto blockvec = PlockY::BlockVectorLoader::load<PlockY::VectorBlock<double>>("../data/blk_files/5b5_withNonSquareBlocks_vector.vblk");
    blockvec.print();
    
    return 0;
}