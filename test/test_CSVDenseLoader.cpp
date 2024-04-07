#include "Plocky/CSVBlockLoaderFactory.hpp"
#include <iostream>
#include <memory>

int main() {
    PlockY::CsvBlockLoader<double> loader;

    // Load a DenseBlock
    std::unique_ptr<PlockY::Block<double>> denseBlock = loader.createDense("mat_shop/dense33.csv", 3, 3);
    std::cout << "Loaded DenseBlock\n";

    // Print the DenseBlock data
    for (int i = 0; i < denseBlock->getRows(); ++i) {
        for (int j = 0; j < denseBlock->getCols(); ++j) {
            std::cout << denseBlock->get(i, j) << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}