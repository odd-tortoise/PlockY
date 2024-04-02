#include "PlockY/SparseBlock.hpp"
#include <iostream>
#include <Eigen/Sparse>
#include "PlockY/BlockLoaderFactory.hpp"
#include "PlockY/CsvBlockLoader.hpp"


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


    std::cout << "Sparse Block reading from CSV file \n";
    PlockY::CsvBlockLoader<double> loader;

    // Load a DenseBlock
    auto sparseBlockLoaded = loader.createSparse("mat_shop/sparse33.csv", 3, 3);
    std::cout << "Loaded sparse Block\n";

    return 0;
}