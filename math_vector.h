//
// Created by vover on 10/24/18.
//

#ifndef ADVANCED_MATH_VECTOR_H
#define ADVANCED_MATH_VECTOR_H

#include <vector>
#include <cstdint>
#include <tgmath.h>

double norm (const std::vector<double> &v);
double scalar_product (const std::vector<double> &v1, const std::vector<double> &v2);
std::vector<double> Projection (const std::vector<double> &a, const std::vector<double> &b);
std::vector<double> Multiply_Coef (const std::vector<double> &a, double coef);
void print_vector(const std::vector<double> &v);

#endif //ADVANCED_MATH_VECTOR_H
