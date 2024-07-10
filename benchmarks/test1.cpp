#include "PlockY.hpp"

int main() {
    /*
    GOLD STANDARD:
    solve with eigen sparse the system fullmat.csv * x = vector.csv
    */

    // load full matrix
    auto fullmat = PlockY::CsvBlockLoader<double>().createSparse("../benchmarks_data/test1/fullmat.csv",60,60)->getMatrix();
    // load vector
    auto vector = PlockY::CsvBlockLoader<double>().createVector("../benchmarks_data/test1/vector.csv",60)->getMatrix();

    Eigen::SparseLU<Eigen::SparseMatrix<double>> solver;
    solver.compute(fullmat);
    Eigen::VectorXd x = solver.solve(vector);

    std::ofstream outFile("test1/gold.txt");
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
    auto blockMatrix_sparse = PlockY::BlockMatrixLoader::load<PlockY::SparseBlock<double>>("../benchmarks_data/test1/blocks.blk");
    // load block vector
    auto blockvec = PlockY::BlockVectorLoader::load<PlockY::VectorBlock<double>>("../benchmarks_data/test1/vector_rhs.vblk");
    // guess
    auto guess = PlockY::BlockVectorLoader::load<PlockY::VectorBlock<double>>("../benchmarks_data/test1/vector_rhs.vblk");
    

    // strategy
    PlockY::Step step_1({0,1});
    PlockY::Step step_2({2});
    PlockY::Strategy strategy({step_1,step_2});

    auto sparseLU_solver = std::make_shared<PlockY::EigenSparseBCGSTAB<double>>();
    PlockY::Solver<PlockY::SparseBlock<double>,PlockY::VectorBlock<double>> solver_sparse(1e-8, 1000, 0.5, strategy, sparseLU_solver);
    solver_sparse.solve(blockMatrix_sparse, blockvec, guess, "test1/");

    return 0;
}