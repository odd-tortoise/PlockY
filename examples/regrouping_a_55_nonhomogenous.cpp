#include "PlockY/Strategy.hpp"
#include "PlockY/BlockMatrixLoader.hpp"
#include "PlockY/BlockMatrix.hpp"
#include <iostream>

int main() {
    
    auto blockMatrix = PlockY::BlockMatrixLoader::load<double>("blk_files/55_diff.blk");
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


    std::cout<<" Strategia doppia: "<<std::endl;
    PlockY::Strategy strategy_doppia(steps_doppia);
    strategy_doppia.print();
    std::cout<<" Regrouping:"<<std::endl;
    blockMatrix.regroup(strategy_doppia);

    return 0;   
}