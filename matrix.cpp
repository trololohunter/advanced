//
// Created by vover on 10/24/18.
//


#include <cstdio>
#include <iostream>
#include "matrix.h"

Matrix::Matrix(uint64_t n) {
    size = n;
    Column_Index.resize(n);
    Data.resize(n);
}

void Matrix::Matrix_resize(uint64_t n) {

    Column_Index.clear();
    Data.clear();

    size = n;
    Column_Index.resize(n);
    Data.resize(n);
}

std::vector<double> Matrix::Matrix_multiply_vector(const std::vector<double> &v) const {
    if (v.size() != size) exit(20);
    uint64_t i, j;
    double res;
    std::vector<double> ans;

    for (i = 0; i < size; ++i) {
        res = 0;
        for (j = 0; j < Column_Index[i].size(); ++j)
            res += Data[i][j] * v[Column_Index[i][j]];
        ans.push_back(res);
    }

    return ans;
}

void Matrix::print() const {
    uint64_t i, j, k;
    double a = 0;
    for (i = 0; i < size; ++i) {
        k = 0;
        for (j = 0; j < size; ++j)
            if (Column_Index[i].empty()
                || k > Column_Index[i].size()
                || Column_Index[i][k] != j) printf("%e \t", a);
            else {
                printf("%e \t", Data[i][k]);
                ++k;
            }
         printf("\n");
    }
}

void Matrix::Add_El(uint64_t i, uint64_t j, double data) {

    if ((i > size) || (j > size)) exit(10);

    auto it = Column_Index[i].begin();
    auto itt = Data[i].begin();
    uint64_t k = 0;

    for (; it < Column_Index[i].end(); ++it, ++k) {
        if (j > *it) continue;
        break;
    }

    if (it == Column_Index[i].end()) {
        Column_Index[i].push_back(j);
        Data[i].push_back(data);
        return;
    }

    if ((!Column_Index[i].empty()) && (j == *it)) exit(30);

    Column_Index[i].insert(it,j);

    while (k > 0)
    {
        --k;
        ++itt;
    }
    Data[i].insert(itt, data);

    return;
}

void Matrix::print_data() const{
    uint64_t i, j;
    for (i = 0; i < size; ++i) {
        for (j = 0; j < Column_Index[i].size(); ++j)
            printf ("%d %e \t", Column_Index[i][j], Data[i][j]);
        printf("next \n");
    }
}
