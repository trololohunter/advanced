//
// Created by vover on 10/24/18.
//

#ifndef ADVANCED_MATH_VECTOR_H
#define ADVANCED_MATH_VECTOR_H

#include <vector>
#include <cstdint>
#include <tgmath.h>

double norm (std::vector<double> v);
double scalar_product (std::vector<double> v1, std::vector<double> v2);
std::vector<double> Proection (std::vector<double> a, std::vector<double> b);
std::vector<double> Myltiply_Coef (std::vector<double> a, double coef);
void print_vector(std::vector<double> v);

#endif //ADVANCED_MATH_VECTOR_H
