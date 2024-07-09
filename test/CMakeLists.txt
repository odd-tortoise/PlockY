FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0 
  )
FetchContent_MakeAvailable(Catch2)

# Get a list of all test source files
file(GLOB TEST_SOURCES "*.cpp")

# Loop over each test source file
foreach(TEST_SOURCE ${TEST_SOURCES})
    # Get the name of the test executable
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)

    # Create the test executable
    add_executable(${TEST_NAME} ${TEST_SOURCE})

    # Link the libraries
    target_link_libraries(${TEST_NAME}
        PUBLIC PlockY
        PRIVATE Catch2::Catch2WithMain
    )

    # Add the test
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()