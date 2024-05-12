#include <catch2/catch_test_macros.hpp>

TEST_CASE("MyClass::add correctly adds two integers", "[MyClass]") {
    
    int result = 2+3;
    REQUIRE(result == 5);

}