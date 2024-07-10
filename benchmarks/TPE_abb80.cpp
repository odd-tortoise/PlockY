#include "PlockY.hpp"

int main() {
    std::cout << " LOADING DATA " << std::endl;

    auto blockMatrix_dense = PlockY::BlockMatrixLoader::load<PlockY::SparseBlock<double>>("data/benchmark_TPE_abb.blk");
    auto blockvec = PlockY::BlockVectorLoader::load<PlockY::VectorBlock<double>>("data/benchmark_TPE_abb.vblk");
    auto guess = PlockY::BlockVectorLoader::load<PlockY::VectorBlock<double>>("data/benchmark_TPE_abb_guess.vblk");

    std::cout << " Creating 2 step strategy for Sparse" << std::endl;
    
    auto sparseLU_solver = std::make_shared<PlockY::EigenSparseLU<double>>();
    auto sparseBS_solver = std::make_shared<PlockY::EigenSparseBCGSTAB<double>>();
    PlockY::Step step_1({0,2,3});
    PlockY::Step step_2({1});
    PlockY::Strategy strat({step_1, step_2});

    std::cout << " SOLVING" << std::endl;
    PlockY::Solver<PlockY::SparseBlock<double>,PlockY::VectorBlock<double>> solver_dense(1e-2, 500, 0.5, strat, sparseBS_solver);
    solver_dense.solve(blockMatrix_dense, blockvec, guess, "out/");
    return 0;
}

#include "PlockY.hpp"

int main() {
    /*
    GOLD STANDARD:
    solve with eigen sparse the system fullmat.csv * x = vector.csv
    */

    // load full matrix
    auto fullmat = PlockY::CsvBlockLoader<double>().createSparse("../benchmarks_data/test0/fullmat.csv",60,60)->getMatrix();
    // load vector
    auto vector = PlockY::CsvBlockLoader<double>().createVector("../benchmarks_data/test0/vector.csv",60)->getMatrix();

    Eigen::SparseLU<Eigen::SparseMatrix<double>> solver;
    solver.compute(fullmat);
    Eigen::VectorXd x = solver.solve(vector);

    std::ofstream outFile("TPE_abb80/gold.txt");
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
    auto blockMatrix_sparse = PlockY::BlockMatrixLoader::load<PlockY::SparseBlock<double>>("../benchmarks_data/TPE_abb80/benchmark_TPE_abb.blk");
    // load block vector
    auto blockvec = PlockY::BlockVectorLoader::load<PlockY::VectorBlock<double>>("../benchmarks_data/TPE_abb80/benchmark_TPE_abb.vblk");
    // guess
    auto guess = PlockY::BlockVectorLoader::load<PlockY::VectorBlock<double>>("../benchmarks_data/TPE_abb80/benchmark_TPE_abb_guess.vblk");
    

    // strategy
    PlockY::Step step_1({0,3});
    PlockY::Step step_2({1,2});
    PlockY::Strategy strategy({step_1,step_2});

    auto sparseLU_solver = std::make_shared<PlockY::EigenSparseLU<double>>();
    PlockY::Solver<PlockY::SparseBlock<double>,PlockY::VectorBlock<double>> solver_sparse(1e-8, 1000, 0.5, strategy, sparseLU_solver);
    solver_sparse.solve(blockMatrix_sparse, blockvec, guess, "TPE_abb80/");

    return 0;
}