//
// Created by vover on 10/24/18.
//


#include "math_vector.h"

double norm (const std::vector<double> &v) {

    double res = 0;

    for (size_t i = 0; i < v.size(); ++i)
        res += v[i] * v[i];

    return sqrt(res);

}

std::vector<double> Multiply_Coef (const std::vector<double> &a, double coef) {

    std::vector<double> ans;

    for (size_t i = 0; i < a.size(); ++i)
        ans.push_back(a[i] * coef);

    return ans;
}

double scalar_product (const std::vector<double> &v1, const std::vector<double> &v2) {

    double res = 0;

    if (v1.size() != v2.size()) exit(40);

    for (size_t i = 0; i < v1.size(); ++i)
        res += v1[i] * v2[i];

    return res;
}

std::vector<double> Projection (const std::vector<double> &a, const std::vector<double> &b) {
    if (a.size() != b.size()) exit(40);

    std::vector<double> ans(a.size(),0);
    double coef;

    coef = scalar_product(a,b) / scalar_product(b,b);
    ans = Multiply_Coef(b, coef);

    return ans;
}

void print_vector(const std::vector<double> &v) {
    size_t i;

    printf("\n\n");
    for (i = 0; i < v.size(); ++i)
        printf ("%e \n", v[i]);
    printf("\n\n");
    return;
}