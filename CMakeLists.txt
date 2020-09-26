cmake_minimum_required(VERSION 3.17)
project(summer_practise)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
add_executable(summer_practise src/common/Geometry.cpp src/common/Geometry.h src/common/Sgn.h src/Graham_scan.cpp src/Graham_scan.h src/NearestNeighbor.cpp src/NearestNeighbor.h tests/test.cpp)
