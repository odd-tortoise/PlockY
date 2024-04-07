#include <iostream>
#include <memory>
#include <cassert>
#include "PlockY/VectorRHSLoader.hpp"
#include "PlockY/VectorRHS.hpp"

int main() {
    PlockY::VectorRHSLoader<double> loader;
    PlockY::VectorRHS<double> vec_RHS = loader.load("blk_files/test.vblk");
    vec_RHS.print();
    return 0;
}