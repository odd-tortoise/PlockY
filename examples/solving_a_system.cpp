#include "PlockY.hpp"

int main() {

    std::cout << " LOADING DATA " << std::endl;
    auto blockMatrix_dense = PlockY::BlockMatrixLoader::load<PlockY::DenseBlock<double>>("../data/blk_files/5b5_withNonSquareBlocks_dense.blk");
    auto blockMatrix_sparse = PlockY::BlockMatrixLoader::load<PlockY::SparseBlock<double>>("../data/blk_files/5b5_withNonSquareBlocks_sparse.blk");
    auto blockvec = PlockY::BlockVectorLoader::load<PlockY::VectorBlock<double>>("../data/blk_files/5b5_withNonSquareBlocks_vector.vblk");
    auto guess = PlockY::BlockVectorLoader::load<PlockY::VectorBlock<double>>("../data/blk_files/5b5guess.vblk");

    std::cout << " Creating 3 step strategy " << std::endl;
    PlockY::Step step_1({0,3});
    PlockY::Step step_2({1});
    PlockY::Step step_3({2});
    PlockY::Strategy strategy_tripla({step_1, step_2, step_3});

    std::cout << " SOLVING DENSE " << std::endl;
    auto denseLU_solver = std::make_shared<PlockY::EigenDenseLU<double>>();
    PlockY::Solver<PlockY::DenseBlock<double>,PlockY::VectorBlock<double>> solver_dense(1e-6, 1000, 0.5, strategy_tripla, denseLU_solver);
    solver_dense.solve(blockMatrix_dense, blockvec, guess);

    std::cout << std::endl;

    std::cout << " SOLVING SPARSE " << std::endl;
    auto sparseLU_solver = std::make_shared<PlockY::EigenSparseLU<double>>();
    PlockY::Solver<PlockY::SparseBlock<double>,PlockY::VectorBlock<double>> solver_sparse(1e-6, 1000, 0.5, strategy_tripla, sparseLU_solver);
    solver_sparse.solve(blockMatrix_sparse, blockvec, guess);
    
    return 0;
} 