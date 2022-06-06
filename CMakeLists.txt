cmake_minimum_required(VERSION 3.0.0)
project(bioinf VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 14)

add_executable(bioinf src/main.cpp src/graph.cpp src/genetic.cpp)
target_include_directories(bioinf PUBLIC headers)