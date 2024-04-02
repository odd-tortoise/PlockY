#include "PlockY/BlockMatrixLoader.hpp"
#include "PlockY/BlockMatrix.hpp"
#include <cassert>

int main() {
    PlockY::BlockMatrixLoader<double> loader;
    PlockY::BlockMatrix<double> blockMatrix = loader.load("blk_files/test.blk");


    return 0;
}