//
// Created by vover on 10/24/18.
//

#include <vector>
#include <cstdint>
#include <cstdlib>

#ifndef ADVANCED_MATRIX_H
#define ADVANCED_MATRIX_H


class Matrix {

    std::vector<std::vector<size_t>> Column_Index;
    std::vector<std::vector<double>> Data;
    size_t size;

public:
    Matrix () {};
    Matrix (size_t n);
    ~Matrix() {};

    void Matrix_resize (size_t n);
    void Add_El (size_t i, size_t j, double data);
    std::vector<double> Matrix_multiply_vector (const std::vector<double> &v) const;
    void print() const;
    void print_data() const;
};


#endif //ADVANCED_MATRIX_H
