# Collect all test source files
file(GLOB EG_SOURCES "*.cpp")

foreach(ex_source ${EG_SOURCES})
    # Get the name of the file without an extension
    get_filename_component(ex_name ${ex_source} NAME_WE)

    # Add executable for this test source
    add_executable(${ex_name} ${ex_source})

    # Link the test executable with the main library
    target_link_libraries(${ex_name} PlockY)
endforeach()