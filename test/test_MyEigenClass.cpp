#include "PlockY/test_w_eigen.hpp"
#include <iostream>
#include <Eigen/Dense>

int main() {
    MyEigenClass myEigenClass;
    Eigen::Vector2d a(1.0, 2.0);
    Eigen::Vector2d b(3.0, 4.0);
    Eigen::Vector2d result = myEigenClass.add(a, b);
    
    if(result == Eigen::Vector2d(4.0, 6.0)) {
        std::cout << "Test passed: MyEigenClass::add correctly adds two vectors.\n";
    } else {
        std::cout << "Test failed: MyEigenClass::add does not correctly add two vectors.\n";
    }

    return 0;
}