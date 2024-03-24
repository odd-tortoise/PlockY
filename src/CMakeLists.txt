
# Make an automatic library - will be static or dynamic based on user setting
#add_library(PlockY ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp ${HEADER_LIST})

# We need this directory, and users of our library will need it too
#target_include_directories(PlockY PUBLIC ../include ../extra)

# All users of this library will need at least C++11
#target_compile_features(PlockY PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
#source_group(
#  TREE "${PROJECT_SOURCE_DIR}/include"
#  PREFIX "Header Files"
#  FILES ${HEADER_LIST})

  # Collect all source files
file(GLOB_RECURSE SOURCES "*.cpp")

# Create a library from the source files
add_library(PlockY ${SOURCES})

# Link the library with Eigen
target_include_directories(PlockY PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../extra/eigen-3.4.0
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)