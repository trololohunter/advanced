cmake_minimum_required(VERSION 3.10)
project(advanced)

set(CMAKE_CXX_STANDARD 11)

add_executable(advanced main.cpp matrix.cpp matrix.h Subspace_Iteration.cpp Subspace_Iteration.h math_vector.cpp matrix.cpp constructionW_row.cpp constructionW_row.h tridiagmatrix.cpp tridiagmatrix.h ChafeInfante_equation.cpp ChafeInfante_equation.h)