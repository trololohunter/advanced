#include <iostream>
#include "matrix.h"

#define SIZE 6

#include "cmake-build-debug/math_vector.h"

int main() {
    int i,j;
    double data;
    Matrix m(SIZE);
    std::vector<double> v;
    for (i = 0; i < SIZE; ++i)
        v.push_back(rand() % 100);

    print_vector(v);

    scanf("%d %d %lf", &i, &j, &data);

    while ((i > -1) && (j > -1))
    {
        m.Add_El(i,j,data);
        m.print_data();
        m.print();
        scanf("%d %d %lf", &i, &j, &data);
    }

    v = m.Matrix_multiply_vector(v);

    print_vector(v);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}