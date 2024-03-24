#include "PlockY/test_no_eigen.hpp"
#include <iostream>

int main() {
    MyClass myClass;
    int result = myClass.add(2, 3);
    
    if(result == 5) {
        std::cout << "Test passed: MyClass::add correctly adds two integers.\n";
    } else {
        std::cout << "Test failed: MyClass::add does not correctly add two integers.\n";
    }

    return 0;
}