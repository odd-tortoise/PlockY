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

  # Docs only available if this is the main app
find_package(Doxygen)
if(Doxygen_FOUND)
    add_subdirectory(docs)
else()
    message(STATUS "Doxygen not found, not building docs")
endif()


# Include Eigen headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extra/eigen)

add_subdirectory(src)
#add_subdirectory(test)
add_subdirectory(examples)