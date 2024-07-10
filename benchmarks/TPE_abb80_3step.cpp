#include "PlockY.hpp"


int main() {
    /*
    GOLD STANDARD:
    solve with eigen sparse the system fullmat.csv * x = vector.csv
    */

    // load full matrix
    auto fullmat = PlockY::CsvBlockLoader<double>().createSparse("../benchmarks_data/ABB_80/LHS_1_full_sparse.csv",2400,2400)->getMatrix();
    // load vector
    auto vector = PlockY::CsvBlockLoader<double>().createVector("../benchmarks_data/ABB_80/RHS0_1_full.csv",2400)->getMatrix();

    Eigen::SparseLU<Eigen::SparseMatrix<double>> solver;
    solver.compute(fullmat);
    Eigen::VectorXd x = solver.solve(vector);

    std::ofstream outFile("TPE_abb80_3step/gold.txt");
    if (outFile.is_open()) {
        outFile << x << std::endl;
        outFile.close();
    } else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }
        
    /*
    PLOCKY:
    solve with plocky the system fullmat.csv * x = vector.csv
    */

    // load block matrix
    auto blockMatrix_sparse = PlockY::BlockMatrixLoader::load<PlockY::SparseBlock<double>>("../benchmarks_data/ABB_80/blocks.blk");
    // load block vector
    auto blockvec = PlockY::BlockVectorLoader::load<PlockY::VectorBlock<double>>("../benchmarks_data/ABB_80/vector_rhs.vblk");
    // guess
    auto guess = PlockY::BlockVectorLoader::load<PlockY::VectorBlock<double>>("../benchmarks_data/ABB_80/guess.vblk");
    

    // strategy - 3 steps F . H . M
    PlockY::Step step_3({0,1,4});
    PlockY::Step step_1({2});
    PlockY::Step step_2({3});
    PlockY::Strategy strategy({step_1,step_2,step_3});

    auto sparseLU_solver = std::make_shared<PlockY::EigenSparseLU<double>>();
    PlockY::Solver<PlockY::SparseBlock<double>,PlockY::VectorBlock<double>> solver_sparse(1e-6, 2000, 0.5, strategy, sparseLU_solver);
    solver_sparse.solve(blockMatrix_sparse, blockvec, guess, "TPE_abb80_3step/");

    return 0;
}