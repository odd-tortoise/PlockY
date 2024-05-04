#include "PlockY/CSVBlockLoaderFactory.hpp"

int main() {
    PlockY::CsvBlockLoader<double> factory;
    auto denseBlock = factory.createDense("mat_shop/dense.csv", 2, 2);
    auto sparseBlock = factory.createSparse("mat_shop/sparse.csv", 4, 4);
    auto vecBlock = factory.createVector("vec_shop/vector.csv", 4);

    denseBlock->print();
    vecBlock->print();
    
    return 0;
}