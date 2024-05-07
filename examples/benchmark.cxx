#include "PlockY/BlockMatrixLoader.hpp"
#include "PlockY/BlockMatrix.hpp"
#include "PlockY/BlockVector.hpp"
#include "PlockY/LUBLockSolver.hpp"
#include "PlockY/BlockVectorLoader.hpp"
#include "PlockY/Solver.hpp"

#include <iostream>
int main() {
    auto blockMatrix = PlockY::BlockMatrixLoader::load<double>("blk_files/benchmark1.blk");
    auto blockVector = PlockY::BlockVectorLoader::load<double>("blk_files/benchmark1.vblk");
    auto guess = PlockY::BlockVectorLoader::load<double>("blk_files/benchmark1.vblk");

    PlockY::LUSolver LUsolver;
    PlockY::Step step_1({0, 2,3}, std::make_shared<PlockY::LUSolver>(LUsolver));
    PlockY::Step step_acc({1},std::make_shared<PlockY::LUSolver>(LUsolver));
    std::vector<PlockY::Step> steps_doppia = {step_1, step_acc};
    PlockY::Strategy strategy_doppia(steps_doppia);

    std::cout<<" -------------- SOLVING  --------------"<<std::endl;
    PlockY::Solver solver(1e-6, 20, 0.5);
    PlockY::BlockVector x = solver.solve(blockMatrix, blockVector, guess, strategy_doppia );
}