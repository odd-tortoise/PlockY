/**
 * @brief This is the main function of the program.
 * 
 * It loads a block matrix and vector right-hand side from files,
 * initializes a guess vector, defines a list of steps for the solver,
 * creates a solver object, and solves the linear system using the
 * loaded matrix, vector, guess, and steps. The solution is then returned.
 * 
 * @return int Returns 0 to indicate successful execution of the program.
 */
#include "PlockY/BlockMatrix.hpp"
#include "PlockY/BlockMatrixLoader.hpp"
#include "PlockY/VectorRHSLoader.hpp"
#include "PlockY/VectorRHS.hpp"
#include "PlockY/Step.hpp"
#include "PlockY/Solver.hpp"

int main() {
    
    PlockY::BlockMatrixLoader<double> loader;
    PlockY::BlockMatrix<double> mat = loader.load("blk_files/test_solver2.blk");

    PlockY::VectorRHSLoader<double> loader_vec;
    PlockY::VectorRHS<double> vec_RHS = loader_vec.load("blk_files/test_solver.vblk");

    PlockY::VectorRHS<double> guess = loader_vec.load("blk_files/test_solver.vblk");

    //std::vector<PlockY::Step> steps = {PlockY::Step({0}, 0),PlockY::Step({1}, 0),PlockY::Step({2}, 0)};
    std::vector<PlockY::Step> steps = {PlockY::Step({0,1}, 0),PlockY::Step({2}, 0)};

    PlockY::Solver solver(1e-6, 10);
    auto sol = solver.solve(mat, vec_RHS, guess, steps);
    
    return 0;
}