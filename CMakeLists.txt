cmake_minimum_required(VERSION  3.14...3.28)

project(
    PlockY 
    VERSION 0.1.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set correct version of c++
set(CMAKE_CXX_STANDARD 17)

# Include Eigen headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extra/eigen-3.4.0)

add_subdirectory(src)
add_subdirectory(test)
