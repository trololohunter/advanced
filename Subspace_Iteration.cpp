//
// Created by vover on 10/24/18.
//

#include <zconf.h>
#include "Subspace_Iteration.h"
#include "math_vector.h"

#define EPS 1e-10

void Subspace_Iteration::resize(size_t m, size_t n) {
    size = m;
    vector_size = n;

    Coordinate.clear();

    Coordinate.resize(m);
    for (int i = 0; i < m; ++i)
        Coordinate[i].resize(n,0);

}

void Subspace_Iteration::Orthogonalization() {
    std::vector<double> a;
    double vector_norm_obr;

    for (size_t num_of_vector = 1; num_of_vector < size; ++num_of_vector) {

        for (size_t j = 0; j < num_of_vector; ++j)
        {
            a = Proection(Coordinate[num_of_vector], Coordinate[j]);
            for (size_t i = 0; i < vector_size; ++i)
                Coordinate[num_of_vector][i] -= a[i];
        }
    }

    for (size_t i = 0; i < size; ++i) {
        vector_norm_obr = 1./norm(Coordinate[i]);
        for (size_t j = 0; j < vector_size; ++j)
            Coordinate[i][j] *= vector_norm_obr;
    }

    return;
}

void Subspace_Iteration::print() const {

    printf("\n Subspace_Iteration Coordinates \n");
    for (size_t i = 0; i < vector_size; ++i) {
        for (size_t j = 0; j < size; ++j)
            printf ("%e \t", Coordinate[j][i]);
        printf("\n");
    }
    printf("\n\n");
}

bool equal(const Subspace_Iteration &A, const Subspace_Iteration &B) {
    double coef;
    std::vector<double> res(A.vector_size, 0);

    if (A.size != B.size || A.vector_size != B.vector_size) exit(50);

    for (size_t i = 0; i < A.size; ++i) {
        for (size_t j = 0; j < A.size; ++j) {
            coef = scalar_product(A.Coordinate[j], B.Coordinate[i]);
            for (size_t k = 0; k < A.vector_size; ++k) {
                res[k] += A.Coordinate[j][k] * coef;
            }
        }
        for (size_t k = 0; k < A.vector_size; ++k) {
            if (res[k] - B.Coordinate[i][k] < EPS) continue;
            else return false;
        }
        res.clear();
        res.resize(A.vector_size,0);
    }

    for (size_t i = 0; i < A.size; ++i) {
        for (size_t j = 0; j < A.size; ++j) {
            coef = scalar_product(A.Coordinate[i], B.Coordinate[j]);
            for (size_t k = 0; k < A.vector_size; ++k) {
                res[k] += B.Coordinate[j][k] * coef;
            }
        }
        for (size_t k = 0; k < A.vector_size; ++k) {
            if (res[k] - A.Coordinate[i][k] < EPS) continue;
            else return false;
        }
        res.clear();
        res.resize(A.vector_size,0);
    }

    return true;
}
