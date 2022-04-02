cmake_minimum_required(VERSION 3.0.0)
project(bioinf VERSION 0.1.0)

set(INCLUDE_DIR /src/headers)

include_directories(${INCLUDE_DIR})

add_executable(bioinf src/main.cpp src/graph.cpp)

