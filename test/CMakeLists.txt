# Collect all test source files
file(GLOB TEST_SOURCES "*.cpp")

foreach(test_source ${TEST_SOURCES})
    # Get the name of the file without an extension
    get_filename_component(test_name ${test_source} NAME_WE)

    # Add executable for this test source
    add_executable(${test_name} ${test_source})

    # Link the test executable with the main library
    target_link_libraries(${test_name} PlockY)
endforeach()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/mat_shop
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/blk_files
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
     file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/vec_shop
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})