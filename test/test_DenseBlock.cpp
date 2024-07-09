#include <catch2/catch_test_macros.hpp>
#include "PlockY/DenseBlock.hpp"

TEST_CASE("DenseBlock methods work correctly", "[DenseBlock]") {
    PlockY::DenseBlock<double> block;  // Create a 5x5 block

    SECTION("Setting and getting a value at the edges") {
        block.set(0, 0, 10.0);  // Set the value at (0, 0) to 10.0
        REQUIRE(block.get(0, 0) == 10.0);  // Check that the value at (0, 0) is now 10.0

        block.set(4, 4, 20.0);  // Set the value at (4, 4) to 20.0
        REQUIRE(block.get(4, 4) == 20.0);  // Check that the value at (4, 4) is now 20.0
    }

    SECTION("Setting and getting a value out of range") {
        REQUIRE_THROWS(block.set(5, 5, 30.0));  // This should throw an exception

        REQUIRE_THROWS(block.get(5, 5));  // This should also throw an exception
    }
}