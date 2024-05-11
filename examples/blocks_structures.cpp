#include "PlockY/BlockMatrixLoader.hpp"
#include "PlockY/BlockMatrix.hpp"
#include "PlockY/BlockVectorLoader.hpp"
#include "PlockY/DenseBlock.hpp"

int main() {

    auto blockMatrix = PlockY::BlockMatrixLoader::load<PlockY::DenseBlock<double>>("blk_files/saddle_point.blk");
    blockMatrix.print();

    auto blockMatrix2 = PlockY::BlockMatrixLoader::load<PlockY::SparseBlock<double>>("blk_files/saddle_point_sparse.blk");
    blockMatrix2.print();

    auto blockvec = PlockY::BlockVectorLoader::load<PlockY::VectorBlock<double>>("blk_files/simple_vector.vblk");
    blockvec.print();

    return 0;
} 