#include "PlockY.hpp"
#include <iostream>

int main() {
    std::cout<< "Loading a block from a .mtx file" << std::endl;
    auto factory = PlockY::MTXBlockLoader<double>();
    auto block = factory.createSparse("../data/mat_shop/sparse/Trefethen_20b.mtx", 0, 0);
    block->print();
    return 0;
}