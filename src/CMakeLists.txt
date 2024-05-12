file(GLOB_RECURSE SOURCES "*.cpp") # si dovrebbe usare una lista di file 

# Create a library from the source files
add_library(PlockY ${SOURCES})

target_include_directories(PlockY 
PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/../include
PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../extra/eigen
)