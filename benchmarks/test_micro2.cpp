#include "PlockY.hpp"

int main() {
    /*
    GOLD STANDARD:
    solve with eigen sparse the system fullmat.csv * x = vector.csv
    */

    // load full matrix
    auto fullmat = PlockY::CsvBlockLoader<double>().createSparse("../benchmarks_data/micro/fullmat.csv",10,10)->getMatrix();
    // load vector
    auto vector = PlockY::CsvBlockLoader<double>().createVector("../benchmarks_data/micro/vector.csv",10)->getMatrix();

    std::cout << "fullmat: " << std::endl << fullmat << std::endl;


    Eigen::SparseLU<Eigen::SparseMatrix<double>> solver;
    solver.compute(fullmat);
    Eigen::VectorXd x = solver.solve(vector);

    std::ofstream outFile("test_micro2/gold.txt");
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
    auto blockMatrix_sparse = PlockY::BlockMatrixLoader::load<PlockY::SparseBlock<double>>("../benchmarks_data/micro/blocks.blk");
    // load block vector
    auto blockvec = PlockY::BlockVectorLoader::load<PlockY::VectorBlock<double>>("../benchmarks_data/micro/vector_rhs.vblk");
    // guess
    auto guess = PlockY::BlockVectorLoader::load<PlockY::VectorBlock<double>>("../benchmarks_data/micro/guess.vblk");
    

    // strategy
    PlockY::Step step_1({0});
    PlockY::Step step_2({1});
    PlockY::Step step_3({2});
    PlockY::Strategy strategy({step_1,step_2,step_3});

    auto sparseLU_solver = std::make_shared<PlockY::EigenSparseLU<double>>();
    PlockY::Solver<PlockY::SparseBlock<double>,PlockY::VectorBlock<double>> solver_sparse(1e-3, 1000, 0.5, strategy, sparseLU_solver);
    solver_sparse.solve(blockMatrix_sparse, blockvec, guess, "test_micro2/", true);

    return 0;
}