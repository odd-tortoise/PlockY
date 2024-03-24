#pragma once

#include <Eigen/Dense>

class MyEigenClass {
public:
    MyEigenClass();
    Eigen::Vector2d add(const Eigen::Vector2d& a, const Eigen::Vector2d& b);
};