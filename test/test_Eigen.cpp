#include <catch2/catch_test_macros.hpp>
#include "PlockY/test_w_eigen.hpp"

TEST_CASE("MyEigenClass::add correctly adds two vector", "[MyEigenClass]") {
    MyEigenClass myEigenClass;
    Eigen::Vector2d a(1, 2);
    Eigen::Vector2d b(3, 4);
    Eigen::Vector2d result2 = myEigenClass.add(a, b);
    REQUIRE(result2(0) == 4);
    REQUIRE(result2(1) == 6);   
}