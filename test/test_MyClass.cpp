#include <catch2/catch_test_macros.hpp>
#include "PlockY/test_no_eigen.hpp"
#include "PlockY/test_w_eigen.hpp"

TEST_CASE("MyClass::add correctly adds two integers", "[MyClass]") {
    MyClass myClass;
    int result = myClass.add(2, 3);
    REQUIRE(result == 5);

    MyEigenClass myEigenClass;
    Eigen::Vector2d a(1, 2);
    Eigen::Vector2d b(3, 4);
    Eigen::Vector2d result2 = myEigenClass.add(a, b);
    REQUIRE(result2(0) == 4);
    REQUIRE(result2(1) == 6);   
}