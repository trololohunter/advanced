//
// Created by vover on 10/24/18.
//


#include "math_vector.h"

double norm (std::vector<double> v) {

    double res = 0;

    for (uint64_t i = 0; i < v.size(); ++i)
        res += v[i] * v[i];

    return sqrt(res);

}

std::vector<double> Myltiply_Coef (std::vector<double> a, double coef) {

    std::vector<double> ans;

    for (uint64_t i = 0; i < a.size(); ++i)
        ans.push_back(a[i] * coef);

    return ans;
}

double scalar_product (std::vector<double> v1, std::vector<double> v2) {

    double res = 0;

    if (v1.size() != v2.size()) exit(40);

    for (uint64_t i = 0; i < v1.size(); ++i)
        res += v1[i] * v2[i];

    return res;
}

std::vector<double> Proection (std::vector<double> a, std::vector<double> b) {
    if (a.size() != b.size()) exit(40);

    std::vector<double> ans(a.size(),0);
    double coef;

    coef = scalar_product(a,b) / scalar_product(b,b);
    ans = Myltiply_Coef(b, coef);

    return ans;
}

void print_vector(std::vector<double> v) {
    uint64_t i;

    printf("\n\n");
    for (i = 0; i < v.size(); ++i)
        printf ("%e \n", v[i]);
    printf("\n\n");
    return;
}