#include "PlockY/BlockMatrixLoader.hpp"
#include "PlockY/BlockMatrix.hpp"
#include <cassert>

int main() {
    PlockY::BlockMatrixLoader<double> loader;
    PlockY::BlockMatrix<double> blockMatrix = loader.load("blk_files/test.blk");

    // Add assertions to check that the BlockMatrix has the expected blocks
    // This will depend on the contents of your test.blk file
    // For example, if the first block in the file is a 2x2 dense block at position (0, 0),
    // you might do something like this:
    std::cout << "Printing blockMatrix" << std::endl;
    //blockMatrix.print();

    std::shared_ptr<PlockY::Block<double>> block = blockMatrix.getBlock(0, 0);
    //assert(block->getType() == "Dense");
    //assert(block->getRows() == 2);
    //assert(block->getCols() == 2);

    

    // Add more assertions as needed...

    return 0;
}