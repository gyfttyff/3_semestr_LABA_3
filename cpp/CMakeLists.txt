
cmake_minimum_required(VERSION 3.10)
project(Lab3_OOP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Главная программа
add_executable(lab3_main main.cpp)
target_include_directories(lab3_main PRIVATE ${CMAKE_SOURCE_DIR})

# GoogleTest
find_package(GTest REQUIRED)
add_executable(lab3_test_gtest tests/test_gtest.cpp)
target_include_directories(lab3_test_gtest PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(lab3_test_gtest GTest::gtest GTest::gtest_main pthread)

# Boost.Test
add_executable(lab3_test_boost tests/test_boost.cpp)
target_include_directories(lab3_test_boost PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(lab3_test_boost pthread)

# Catch2
add_executable(lab3_test_catch tests/test_catch.cpp)
target_include_directories(lab3_test_catch PRIVATE ${CMAKE_SOURCE_DIR})

# Google Benchmark
find_package(benchmark QUIET)
if (benchmark_FOUND)
    add_executable(lab3_bench bench/bench.cpp)
    target_include_directories(lab3_bench PRIVATE ${CMAKE_SOURCE_DIR})
    target_link_libraries(lab3_bench PRIVATE benchmark::benchmark pthread)
    target_compile_options(lab3_bench PRIVATE -O2)
endif()