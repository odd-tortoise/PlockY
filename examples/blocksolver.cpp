#include "PlockY.hpp"

int main() {

    std::cout << " LOADING DATA " << std::endl;

    auto blockMatrix_dense = PlockY::BlockMatrixLoader::load<PlockY::DenseBlock<double>>("../data/blk_files/5b5_withNonSquareBlocks.blk");
    //auto blockMatrix_sparse = PlockY::BlockMatrixLoader::load<PlockY::SparseBlock<double>>("blk_files/saddle_point_sparse.blk");
    auto blockvec = PlockY::BlockVectorLoader::load<PlockY::VectorBlock<double>>("../data/blk_files/5b5_withNonSquareBlocks_vector.vblk");
    auto guess = PlockY::BlockVectorLoader::load<PlockY::VectorBlock<double>>("../data/blk_files/5b5_withNonSquareBlocks_vector.vblk");

    std::cout << " Creating 3 step strategy for DENSE" << std::endl;
    
    auto denseLU_solver = std::make_shared<PlockY::EigenDenseLU<double>>();
    PlockY::Step step_1_dense({0,3});
    PlockY::Step step_2_dense({1});
    PlockY::Step step_3_dense({2});
    PlockY::Strategy strategy_tripla_dense({step_1_dense, step_2_dense, step_3_dense});

    std::cout << " SOLVING DENSE" << std::endl;
    PlockY::Solver<PlockY::DenseBlock<double>,PlockY::VectorBlock<double>> solver_dense(1e-6, 100, 0.5, strategy_tripla_dense, denseLU_solver);
    solver_dense.solve(blockMatrix_dense, blockvec, guess);
    
    return 0;
} 