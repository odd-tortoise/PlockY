#include "PlockY/Strategy.hpp"
#include "PlockY/BlockMatrixLoader.hpp"
#include "PlockY/BlockMatrix.hpp"
#include "PlockY/BlockVectorLoader.hpp"

#include <iostream>

int main() {

    std::cout<<"################DENSE######################"<<std::endl;
    
    auto blockMatrix = PlockY::BlockMatrixLoader::load<PlockY::DenseBlock<double>>("blk_files/5b5_withNonSquareBlocks.blk");
    blockMatrix.print();

    PlockY::Step step_1({0,3});
    PlockY::Step step_2({1});
    PlockY::Step step_3({2});
    PlockY::Step step_acc({1,2});
    std::vector<PlockY::Step> steps_tripla = {step_1, step_2, step_3};
    std::vector<PlockY::Step> steps_doppia = {step_1, step_acc};
   

   
    std::cout<<" Strategia tripla: "<<std::endl;
    PlockY::Strategy strategy_tripla(steps_tripla);
    strategy_tripla.print();
    std::cout<<" Regrouping:"<<std::endl;
    blockMatrix.regroup(strategy_tripla);
    for (int i = 0; i < 3; i++) {
        std::cout << "LHS block " << i << std::endl;
        std::cout<< blockMatrix.get_lhs(i)<<std::endl;
    }
    for (int i = 0; i < 3; i++) {
        std::cout << "RHS block " << i << std::endl;
        std::cout<< blockMatrix.get_corr(i)<<std::endl;
    }



    std::cout<<" Strategia doppia: "<<std::endl;
    PlockY::Strategy strategy_doppia(steps_doppia);
    strategy_doppia.print();
    std::cout<<" Regrouping:"<<std::endl;
    blockMatrix.regroup(strategy_doppia);
    for (int i = 0; i < 2; i++) {
        std::cout << "LHS block " << i << std::endl;
        std::cout<< blockMatrix.get_lhs(i)<<std::endl;
    }
    for (int i = 0; i < 2; i++) {
        std::cout << "RHS block " << i << std::endl;
        std::cout<< blockMatrix.get_corr(i)<<std::endl;
    }

    std::cout<<"################SPARSE######################"<<std::endl;

    auto blockMatrixSparse = PlockY::BlockMatrixLoader::load<PlockY::SparseBlock<double>>("blk_files/5b5_withNonSquareBlocks_sparse.blk");
    blockMatrixSparse.print();

    std::cout<<" Strategia tripla: "<<std::endl;
    strategy_tripla.print();
    std::cout<<" Regrouping:"<<std::endl;
    blockMatrixSparse.regroup(strategy_tripla);
    for (int i = 0; i < 3; i++) {
        std::cout << "LHS block " << i << std::endl;
        std::cout<< Eigen::MatrixXd(blockMatrixSparse.get_lhs(i))<<std::endl;
    }
    for (int i = 0; i < 3; i++) {
        std::cout << "RHS block " << i << std::endl;
        std::cout<< Eigen::MatrixXd(blockMatrixSparse.get_corr(i))<<std::endl;
    }


    std::cout<<" Strategia doppia: "<<std::endl;
    strategy_doppia.print();
    std::cout<<" Regrouping:"<<std::endl;
    blockMatrixSparse.regroup(strategy_doppia);
    for (int i = 0; i < 2; i++) {
        std::cout << "LHS block " << i << std::endl;
        std::cout<< Eigen::MatrixXd(blockMatrixSparse.get_lhs(i))<<std::endl;
    }
    for (int i = 0; i < 2; i++) {
        std::cout << "RHS block " << i << std::endl;
        std::cout<< Eigen::MatrixXd(blockMatrixSparse.get_corr(i))<<std::endl;
    }


    std::cout<<"################VECTOR######################"<<std::endl;

    auto blockVector = PlockY::BlockVectorLoader::load<PlockY::VectorBlock<double>>("blk_files/5b5_withNonSquareBlocks_vector.vblk");
    blockVector.print();

    std::cout<<" Strategia tripla: "<<std::endl;
    strategy_tripla.print();
    std::cout<<" Regrouping:"<<std::endl;
    blockVector.regroup(strategy_tripla);
    for (int i = 0; i < 3; i++) {
        std::cout << "Vector block " << i << std::endl;
        std::cout<< blockVector.get_rhs(i)<<std::endl;
    }

    std::cout<<" Strategia doppia: "<<std::endl;
    strategy_doppia.print();
    std::cout<<" Regrouping:"<<std::endl;
    blockVector.regroup(strategy_doppia);
    for (int i = 0; i < 2; i++) {
        std::cout << "Vector block " << i << std::endl;
        std::cout<< blockVector.get_rhs(i)<<std::endl;
    }

    return 0;   
}