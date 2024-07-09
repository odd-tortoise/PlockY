#include "PlockY.hpp"
#include <iostream>

int main() {

    std::cout << "Regrouping a 5x5 matrix with non-homogeneous blocks:\n"
            << "block 0 of size 4 \n"
            << "blocks 1,2,3 of size 2" << std::endl;

    
    auto blockMatrix = PlockY::BlockMatrixLoader::load<PlockY::DenseBlock<double>>("../data/blk_files/5b5_withNonSquareBlocks_dense.blk");
    blockMatrix.print();

    PlockY::Step step_1({0,3});
    PlockY::Step step_2({1});
    PlockY::Step step_3({2});
    PlockY::Step step_acc({1,2});
    PlockY::Strategy triple_strat({step_1, step_2, step_3});
    PlockY::Strategy double_strat({step_1, step_acc});
   
    std::cout << std::endl;
    std::cout<<" ------ Triple Step Strategy ------"<<std::endl;
    triple_strat.print();
    std::cout<<" Regrouping:"<<std::endl;
    blockMatrix.regroup(triple_strat);
    for (int i = 0; i < 3; i++) {
        std::cout << "LHS block " << i << std::endl;
        std::cout<< blockMatrix.get_lhs(i)<<std::endl;
    }
    for (int i = 0; i < 3; i++) {
        std::cout << "RHS block " << i << std::endl;
        std::cout<< blockMatrix.get_corr(i)<<std::endl;
    }

    std::cout << std::endl;
    std::cout<<" ------ Double Step Strategy ------"<<std::endl;
    double_strat.print();
    std::cout<<" Regrouping:"<<std::endl;
    blockMatrix.regroup(double_strat);
    for (int i = 0; i < 2; i++) {
        std::cout << "LHS block " << i << std::endl;
        std::cout<< blockMatrix.get_lhs(i)<<std::endl;
    }
    for (int i = 0; i < 2; i++) {
        std::cout << "RHS block " << i << std::endl;
        std::cout<< blockMatrix.get_corr(i)<<std::endl;
    }

    return 0;   
}