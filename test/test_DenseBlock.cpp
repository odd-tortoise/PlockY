#include "PlockY/DenseBlock.hpp"
#include "PlockY/BlockLoaderFactory.hpp"
#include "PlockY/CsvBlockLoader.hpp"
#include <iostream>
#include <Eigen/Dense>

int main() {
    // Create a DenseBlock of type int
    PlockY::DenseBlock<int> denseBlock(2, 2);

    // Set some values
    denseBlock.set(0, 0, 1);
    denseBlock.set(0, 1, 2);
    denseBlock.set(1, 0, 3);
    denseBlock.set(1, 1, 4);

    // Check the values
    if (denseBlock.get(0, 0) == 1 && denseBlock.get(0, 1) == 2 &&
        denseBlock.get(1, 0) == 3 && denseBlock.get(1, 1) == 4) {
        std::cout << "Test passed: DenseBlock correctly stores and retrieves values.\n";
    } else {
        std::cout << "Test failed: DenseBlock does not correctly store and retrieve values.\n";
    }

    std::cout << "DenseBlock reading from CSV file \n";
    PlockY::CsvBlockLoader<double> loader;

    // Load a DenseBlock
    auto denseBlockLoaded = loader.createDense("mat_shop/dense33.csv", 3, 3);
    std::cout << "Loaded DenseBlock\n";

    return 0;
}