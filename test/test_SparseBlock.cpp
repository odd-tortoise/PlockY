#include "PlockY/SparseBlock.hpp"
#include <iostream>
#include <Eigen/Sparse>

int main() {
    // Create a SparseBlock of type double
    PlockY::SparseBlock<double> sparseBlock(2, 2);

    // Set some values
    sparseBlock.set(0, 0,1.0);
    sparseBlock.set(0, 1,2.0);
    sparseBlock.set(1, 0,3.0);
    sparseBlock.set(1, 1, 4.0);

    // Check the values
    if(sparseBlock.get(0, 0) == 1.0 && sparseBlock.get(0, 1) == 2.0 &&
       sparseBlock.get(1, 0) == 3.0 && sparseBlock.get(1, 1) == 4.0) {
        std::cout << "Test passed: SparseBlock correctly stores and retrieves values.\n";
    } else {
        std::cout << "Test failed: SparseBlock does not correctly store and retrieve values.\n";
    }

    return 0;
}