cmake_minimum_required(VERSION 3.20)
project(sum_amounts LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(sum_amounts src/sum_amounts.cpp)
target_include_directories(sum_amounts PUBLIC include)

add_executable(sum_amounts_tests tests/test_sum_amounts.cpp)
target_link_libraries(sum_amounts_tests PRIVATE sum_amounts)

enable_testing()
add_test(NAME sum_amounts_tests COMMAND sum_amounts_tests)
