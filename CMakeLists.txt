cmake_minimum_required(VERSION  3.14...3.28)

project(
    PlockY 
    VERSION 0.1.0
    LANGUAGES CXX)

# Set correct version of c++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# visual studio and Xcode organization
set_property(GLOBAL PROPERTY USE_FOLDERS ON)



# Include Eigen headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extra/eigen-3.4.0)

add_subdirectory(src)
#add_subdirectory(test)
add_subdirectory(examples)


cmake_minimum_required(VERSION 3.14...3.28)

project(
    PlockY 
    VERSION 0.1.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Find Eigen
find_package(Eigen3 3.4 REQUIRED NO_MODULE)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(examples)

# Set correct version of c++ and include Eigen headers for each target
foreach(target IN ITEMS PlockY test examples)
    target_compile_features(${target} PRIVATE cxx_std_17)
    target_link_libraries(${target} Eigen3::Eigen)
endforeach()