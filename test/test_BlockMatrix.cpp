#include "PlockY/DenseBlock.hpp"
#include "PlockY/SparseBlock.hpp"
#include "PlockY/BlockMatrix.hpp"
#include <iostream>

int main() {
    
    auto block1 = std::make_unique<PlockY::DenseBlock<double>>(2, 2);

    // Set some values
    block1->set(0, 0, 1.0);
    block1->set(0, 1, 2.0);
    block1->set(1, 0, 3.0);
    block1->set(1, 1, 4.0);

    auto block2 = std::make_unique<PlockY::SparseBlock<double>>(2, 2);

    // Set some values
    block2->set(0, 0, -1.0);
    block2->set(0, 1,-2.0);
    block2->set(1, 0,-3.0);
    block2->set(1, 1,-4.0);

    PlockY::BlockMatrix<double> blockMatrix;  // Adjust size as needed

    // Add the Blocks to the BlockMatrix
    blockMatrix.setBlock(0, 0, std::move(block1));
    blockMatrix.setBlock(1, 1, std::move(block2));

    // Retrieve the blocks from the BlockMatrix
    /*auto retrievedBlock1 = blockMatrix.getBlock(0, 0);
    auto retrievedBlock2 = blockMatrix.getBlock(1, 1);


    // Check if the retrieved blocks have the expected values
    bool passed = true;

    if (retrievedBlock1) {
        if (retrievedBlock1->get(0, 0) != 1.0 ||
            retrievedBlock1->get(0, 1) != 2.0 ||
            retrievedBlock1->get(1, 0) != 3.0 ||
            retrievedBlock1->get(1, 1) != 4.0) {
            passed = false;
        }
    }

    if (retrievedBlock2) {
        if (retrievedBlock2->get(0, 0) != -1.0 ||
            retrievedBlock2->get(0, 1) != -2.0 ||
            retrievedBlock2->get(1, 0) != -3.0 ||
            retrievedBlock2->get(1, 1) != -4.0) {
            passed = false;
        }
    }

    // Print the result
    if (passed) {
        std::cout << "Check passed: The retrieved blocks have the expected values." << std::endl;
    } else {
        std::cout << "Check failed: The retrieved blocks do not have the expected values." << std::endl;
    }
    */
    return 0;
}