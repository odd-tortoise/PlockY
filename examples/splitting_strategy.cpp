#include "PlockY/Strategy.hpp"

int main() {
    std::cout << " SPLITTING STRATEGY EXAMPLE " << std::endl;
    std::cout << " We consider a matrix with 5 blocks: 0,1,2,3,4 " << std::endl;

    std::cout << " -------------------------- " << std::endl;
    std::cout << " Strategy with 2 steps: (0,1,4) - (2,3) " << std::endl;
    PlockY::Step step1({0,1,4});
    PlockY::Step step2({2,3});
    std::vector<PlockY::Step> steps = {step1, step2};
    PlockY::Strategy strategy(steps);
    strategy.print();
    
    auto comple1 = strategy.get_complementary_blocks(0);
    auto comple2 = strategy.get_complementary_blocks(1);

    std::cout << "Complementary blocks for step 1: ";
    for (auto i : comple1) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "Complementary blocks for step 2: ";
    for (auto i : comple2) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    

    std::cout << " -------------------------- " << std::endl;
    std::cout << " Strategy with 3 steps: (0,1,4) - (2) - (3) " << std::endl;

    PlockY::Step step_1({0,1,4});
    PlockY::Step step_2({2});
    PlockY::Step step_3({3});
    std::vector<PlockY::Step> steps_tripli = {step_1, step_2, step_3};
    PlockY::Strategy strategy_tripla(steps_tripli);
    strategy_tripla.print();

    auto comple_1 = strategy_tripla.get_complementary_blocks(0);
    auto comple_2 = strategy_tripla.get_complementary_blocks(1);
    auto comple_3 = strategy_tripla.get_complementary_blocks(2);

    std::cout << "Complementary blocks for step 1: ";
    for (auto i : comple_1) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "Complementary blocks for step 2: ";
    for (auto i : comple_2) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "Complementary blocks for step 3: ";   
    for (auto i : comple_3) {
        std::cout << i << " ";
    }


    return 0;
}