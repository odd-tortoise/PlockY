#include "PlockY/Solver.hpp"
#include "PlockY/BlockMatrixLoader.hpp"
#include "PlockY/BlockMatrix.hpp"
#include "PlockY/BlockVector.hpp"
#include "PlockY/BlockVectorLoader.hpp"
#include "PlockY/LUBlockSolver.hpp"

#include <iostream>

int main()
{
    std::cout<<"-------------- LOAD BLOCK MATRIX --------------"<<std::endl;
    auto blockMatrix = PlockY::BlockMatrixLoader::load<double>("blk_files/5b5_for_solver.blk");
    blockMatrix.print();
    std::cout<<"-------------- LOAD BLOCK VECTOR --------------"<<std::endl;
    auto blockVector = PlockY::BlockVectorLoader::load<double>("blk_files/5v_for_solver.vblk");
    blockVector.print();
    std::cout<<"-------------- LOAD BLOCK GUESS --------------"<<std::endl;
    auto guess = PlockY::BlockVectorLoader::load<double>("blk_files/5v_guess_for_solver.vblk");
    guess.print();
    std::cout<<"=============================================="<<std::endl;
    
    PlockY::LUSolver LUsolver;

    PlockY::Step step_1({0, 1, 4}, std::make_shared<PlockY::LUSolver>(LUsolver));
    PlockY::Step step_acc({2,3},std::make_shared<PlockY::LUSolver>(LUsolver));
    std::vector<PlockY::Step> steps_doppia = {step_1, step_acc};
    PlockY::Strategy strategy_doppia(steps_doppia);

    PlockY::Solver solver(1e-6, 5, 0.5);
    PlockY::BlockVector x = solver.solve(blockMatrix, blockVector, guess, strategy_doppia );

    // Print the solution
    std::cout<<"Solution:"<<std::endl;
    x.print();

    return 0;
}