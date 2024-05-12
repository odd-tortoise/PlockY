#include "PlockY.hpp"
#include <iostream>


int main() {
    PlockY::CsvBlockLoader<double> factory;
    auto denseBlock = factory.createDense("../data/mat_shop/dense.csv", 2, 2);
    auto denseBlock2 = factory.createDense("../data/mat_shop/dense2.csv", 2, 2);

    auto sparseBlock = factory.createSparse("../data/mat_shop/sparse.csv", 4, 4);
    auto vecBlock = factory.createVector("../data/vec_shop/vector.csv", 4);

    denseBlock->print();
    vecBlock->print();
    sparseBlock->print();
    std::cout<<"fin qua ok"<<std::endl;
    
    PlockY::BlockMatrix<PlockY::DenseBlock<double>> blockMatrix;
    blockMatrix.setBlock(0, 0, std::move(denseBlock), PlockY::BlockSpec::Normal);
    blockMatrix.setBlock(1, 1, std::move(denseBlock2), PlockY::BlockSpec::Normal);

    auto block = blockMatrix.getBlock(0, 0);
    block->print();

    blockMatrix.print();
    
    return 0;
}