//
// Created by vover on 10/24/18.
//

#include <vector>
#include <cstdint>
#include <cstdlib>

#ifndef ADVANCED_MATRIX_H
#define ADVANCED_MATRIX_H


class Matrix {

    std::vector<std::vector<uint64_t>> Column_Index;
    std::vector<std::vector<double>> Data;
    uint64_t size;

public:
    Matrix ();
    Matrix (uint64_t n);
    ~Matrix()
    {
        Column_Index.clear();
        Data.clear();
    }

    void Matrix_resize (uint64_t n);
    void Add_El (uint64_t i, uint64_t j, double data);
    std::vector<double> Matrix_multiply_vector (const std::vector<double> &v);
    void print();
    void print_data();
};


#endif //ADVANCED_MATRIX_H
