#include "PlockY/DenseBlock.hpp"
#include <iostream>
#include <Eigen/Dense>

int main() {
    // Create a DenseBlock of type double

    PlockY::DenseBlock<double> denseBlock(2, 2);

    // Set some values
    denseBlock.set(0, 0,1.0);
    denseBlock.set(0, 1,2.0);
    denseBlock.set(1, 0,3.0);
    denseBlock.set(1, 1,4.0);

    // Check the values
    if(denseBlock.get(0, 0) == 1.0 && denseBlock.get(0, 1) == 2.0 &&
       denseBlock.get(1, 0) == 3.0 && denseBlock.get(1, 1) == 4.0) {
        std::cout << "Test passed: DenseBlock correctly stores and retrieves values.\n";
    } else {
        std::cout << "Test failed: DenseBlock does not correctly store and retrieve values.\n";
    }

    return 0;
}