#include "PlockY/Strategy.hpp"

int main() {
    PlockY::Step step1({1, 2, 5});
    PlockY::Step step2({3,4});
    std::vector<PlockY::Step> steps = {step1, step2};
    PlockY::Strategy strategy(steps);
    strategy.print();
    
    auto comple1 = strategy.get_complementary_blocks(0);
    auto comple2 = strategy.get_complementary_blocks(1);

    std::cout << "STRATEGY 1: Complementary blocks for step 1: ";
    for (auto i : comple1) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "STRATEGY 1: Complementary blocks for step 2: ";
    for (auto i : comple2) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout<< "--------------------------"<<std::endl;

    std::vector<PlockY::Step> steps_invertiti = {step2, step1};
    PlockY::Strategy strategy_inv(steps_invertiti);
    strategy_inv.print();
    std::cout<< "--------------------------"<<std::endl;



    PlockY::Step step_1({1, 2, 5});
    PlockY::Step step_2({3});
    PlockY::Step step_3({4});
    std::vector<PlockY::Step> steps_tripli = {step_1, step_2, step_3};
    PlockY::Strategy strategy_tripla(steps_tripli);
    strategy_tripla.print();

    auto comple_1 = strategy_tripla.get_complementary_blocks(0);
    auto comple_2 = strategy_tripla.get_complementary_blocks(1);
    auto comple_3 = strategy_tripla.get_complementary_blocks(2);

    std::cout << "STRATEGY 2: Complementary blocks for step 1: ";
    for (auto i : comple_1) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "STRATEGY 2: Complementary blocks for step 2: ";
    for (auto i : comple_2) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "STRATEGY 2: Complementary blocks for step 3: ";   
    for (auto i : comple_3) {
        std::cout << i << " ";
    }


    return 0;
}