#include <iostream>
#include "matrix.h"
#include "Subspace_Iteration.h"

#define SIZE 6

#include "math_vector.h"


int main() {
    int i,j;
    double data;
    Matrix m(SIZE);
    std::vector<double> v;
    for (i = 0; i < SIZE; ++i)
        v.push_back(rand() % 100);

    print_vector(v);
/*
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
*/
    Subspace_Iteration A;
    Subspace_Iteration B;

    A.resize(3,4);
    A.Coordinate[0][0] = 1;
    A.Coordinate[0][1] = 1;
    A.Coordinate[0][2] = 0;
    A.Coordinate[0][3] = 0;
    A.Coordinate[1][0] = 0;
    A.Coordinate[1][1] = -1;
    A.Coordinate[1][2] = 1;
    A.Coordinate[1][3] = 0;
    A.Coordinate[2][0] = 0;
    A.Coordinate[2][1] = 0;
    A.Coordinate[2][2] = -1;
    A.Coordinate[2][3] = 1;


    A.print();
    A.Orthogonalization();
    A.print();

    B.resize(3,4);
    B.Coordinate[0] = A.Coordinate[0];
    B.Coordinate[1] = A.Coordinate[1];
    B.Coordinate[2] = A.Coordinate[2];
    B.print();

    if (equal(A,B)) printf("jafdlksadfahgd \n");

    std::cout << "Hello, World!" << std::endl;
    return 0;
}