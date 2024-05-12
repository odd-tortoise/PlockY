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

option(BUILD_EXAMPLES "Build the examples" ON)
option(BUILD_TESTS "Build the tests" ON)
option(BUILD_DOCS "Build the documentation" ON)

# Submodules for dependencies (just eigen for now)
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extra/eigen)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(src)

if (BUILD_EXAMPLES)
    message(STATUS "Building Examples.")
    add_subdirectory(examples)
endif()

if (BUILD_TESTS)
    message(STATUS "Building tests.")
    include(CTest)
    add_subdirectory(test)
endif()

find_package(Doxygen)
if(DOXYGEN_FOUND AND BUILD_DOCS)
    message(STATUS "Building Docs.")
    add_subdirectory(docs)
else()
    message("Doxygen need to be installed to generate the doxygen documentation")
endif()