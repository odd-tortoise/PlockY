#include "PlockY/CSVBlockLoaderFactory.hpp"
#include "PlockY/BlockMatrix.hpp"
#include <iostream>
#include "PlockY/TransposeOf.hpp"
int main() {
    PlockY::CsvBlockLoader<double> factory;
    auto denseBlock = factory.createDense("mat_shop/dense.csv", 2, 2);
    auto denseBlock2 = factory.createDense("mat_shop/dense2.csv", 2, 2);


    auto sparseBlock = factory.createSparse("mat_shop/sparse.csv", 4, 4);
    auto vecBlock = factory.createVector("vec_shop/vector.csv", 4);

    denseBlock->print();
    vecBlock->print();
    std::cout<<"fin qua ok"<<std::endl;
    
    PlockY::BlockMatrix<PlockY::DenseBlock<double>> blockMatrix;
    blockMatrix.setBlock(0, 0, std::move(denseBlock));
    blockMatrix.setBlock(1, 1, std::move(denseBlock2));
    blockMatrix.setBlock(2, 2, std::make_unique<PlockY::TransposeOf<PlockY::DenseBlock<double>>>(blockMatrix.getBlock(0, 0)));

    auto block = blockMatrix.getBlock(0, 0);
    block->print();

    blockMatrix.print();
    
    return 0;
}