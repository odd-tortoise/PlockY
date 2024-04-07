#include "PlockY/BlockMatrix.hpp"
#include "PlockY/BlockMatrixLoader.hpp"

int main() {
    PlockY::BlockMatrixLoader<double> loader;
    PlockY::BlockMatrix<double> mat = loader.load("blk_files/test.blk");
    //mat.print();
    return 0;
}