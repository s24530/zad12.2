enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(runTests main.cpp test_calculator.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread calculator)

add_test(AllTests runTests)
