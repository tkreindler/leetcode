cmake_minimum_required(VERSION 3.22.2)

project(testProject
    VERSION 1.0
    DESCRIPTION "A test project"
    LANGUAGES CXX)

# this is horrible practice but simulates leetcode well
add_executable(main
    src/main.cpp)

target_compile_features(main PRIVATE cxx_std_17)
