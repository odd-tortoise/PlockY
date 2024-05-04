file(GLOB_RECURSE SOURCES "*.cpp")

# Create a library from the source files
add_library(PlockY ${SOURCES})

# Link the library with Eigen
target_include_directories(PlockY PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../extra/eigen-3.4.0
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)