cmake_minimum_required(VERSION 3.10)
project(Calculator)

set(CMAKE_CXX_STANDARD 14)

# Enable testing
enable_testing()

# Compiler flags for coverage (GCC/G++)
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)

# Target to generate coverage report using gcovr
add_custom_target(coverage
    COMMAND gcovr --html-details -o coverage/index.html
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating code coverage report"
)

# Optionally, you can create a target to clean coverage data
add_custom_target(clean-coverage
    COMMAND rm -rf ${CMAKE_BINARY_DIR}/coverage ${CMAKE_BINARY_DIR}/*.gc*
    COMMENT "Cleaning code coverage data"
)
