#include <iostream>
#include "PlockY/LUBlockSolver.hpp"
#include "PlockY/CSVBlockLoaderFactory.hpp"
#include "PlockY/CSVVecBlockLoader.hpp"
#include "PlockY/Block.hpp"

int main() {
    // Create an instance of LUBlockSolver
    PlockY::LUSolver solver;
    PlockY::CsvBlockLoader<double> loader;
    PlockY::CSVVecBlockLoader<double> vectorLoader;

    // Load a DenseBlock
    std::unique_ptr<PlockY::DenseBlock<double>> denseBlock = loader.createDense("mat_shop/dense33.csv", 3, 3);
    std::unique_ptr<Eigen::VectorXd> vec_rhs = vectorLoader.createBlock("vec_shop/vec3.csv");
    // TODO: Add your test code here
    Eigen::VectorXd result = solver.solve(denseBlock->getMatrix(), *vec_rhs);
    std::cout << "Result: " << result << std::endl;

    
    return 0;
}