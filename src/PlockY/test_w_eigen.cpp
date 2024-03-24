#include "PlockY/test_w_eigen.hpp"

MyEigenClass::MyEigenClass() {}

Eigen::Vector2d MyEigenClass::add(const Eigen::Vector2d& a, const Eigen::Vector2d& b) {
    return a + b;
}