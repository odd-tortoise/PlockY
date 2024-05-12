cmake_minimum_required(VERSION  3.14)

project(
    PlockY 
    VERSION 0.1.0
    LANGUAGES CXX)

message(STATUS "Building ${PROJECT_NAME} version ${VERSION_STRING}")

# Set correct version of c++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "Compiling with C++ standard: ${CMAKE_CXX_STANDARD}")


option(BUILD_EXAMPLES "Build the examples" ON)
option(BUILD_DOCS "Build the Doxygen documentation" ON)

if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    option(BUILD_TESTS "Build tests" ON)
else()
    set(BUILD_TESTS OFF)
endif()


# visual studio and Xcode organization
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Submodules for dependencies (just eigen for now)
# find_package(Git QUIET)
# if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
#    option(GIT_SUBMODULE "Check submodules during build" ON)
#    if(GIT_SUBMODULE)
#        message(STATUS "Submodule update")
#        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
#                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
#        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
#            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
#        endif()
#    endif()
# endif()

Include(FetchContent)
FetchContent_Declare(
      Eigen
      GIT_REPOSITORY    https://gitlab.com/libeigen/eigen.git
      GIT_TAG           master
    )
FetchContent_MakeAvailable(Eigen)



add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/extra/eigen
)

if ((BUILD_EXAMPLES OR BUILD_TESTS))
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

if (BUILD_EXAMPLES)
    message(STATUS "Building Examples.")
    add_subdirectory(examples)
endif()

if (BUILD_TESTS)
    include(CTest)
    message(STATUS "Building tests.")
    add_subdirectory(test)
endif()

find_package(Doxygen)
if(DOXYGEN_FOUND AND BUILD_DOCS)
    message(STATUS "Building Docs.")
    add_subdirectory(docs)
else()
    message("Doxygen need to be installed to generate the doxygen documentation")
endif()