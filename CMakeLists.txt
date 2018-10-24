cmake_minimum_required(VERSION 3.10)
project(advanced)

set(CMAKE_CXX_STANDARD 11)

add_executable(advanced main.cpp matrix.cpp matrix.h Subspace_Iteration.cpp Subspace_Iteration.h cmake-build-debug/math_vector.h cmake-build-debug/math_vector.cpp)