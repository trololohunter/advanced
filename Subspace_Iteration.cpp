//
// Created by vover on 10/24/18.
//

#include <zconf.h>
#include <ctime>
#include <random>
#include "Subspace_Iteration.h"
#include "math_vector.h"

#define EPS 1e-10
#define DEBUG true


void Subspace_Iteration::resize(size_t m, size_t n) {
    size = m;
    vector_size = n;


    CurrCoord.resize(m);
    PrevCoord.resize(m);
    for (int i = 0; i < m; ++i) {
        CurrCoord[i].resize(n, 0);
        PrevCoord[i].resize(n, 0);
    }

}

void Subspace_Iteration::Orthogonalization() {
    std::vector<double> a;
    double vector_norm_obr;

    for (size_t num_of_vector = 1; num_of_vector < size; ++num_of_vector) {

        for (size_t j = 0; j < num_of_vector; ++j)
        {
            a = Projection(CurrCoord[num_of_vector], CurrCoord[j]);
            for (size_t i = 0; i < vector_size; ++i)
                CurrCoord[num_of_vector][i] -= a[i];
        }
    }

    for (size_t i = 0; i < size; ++i) {
        vector_norm_obr = 1./norm(CurrCoord[i]);
        for (size_t j = 0; j < vector_size; ++j)
            CurrCoord[i][j] *= vector_norm_obr;
    }

    if (DEBUG) {
        bool flag = true;

        for (size_t i = 0; i < size; ++i)
        {
            for (size_t j = i+1; j < size; ++j)
                if (scalar_product(CurrCoord[i], CurrCoord[j]) < EPS) continue;
                else flag = false;
        }

        if (flag)
            printf ("SUCCESS, vectors are orthogonal \n");
        else
            printf ("vectors are not orthogonal \n");
    }


    return;
}

void Subspace_Iteration::print() const {

    printf("\n Subspace_Iteration Coordinates \n");
    for (size_t i = 0; i < vector_size; ++i) {
        for (size_t j = 0; j < size; ++j)
            printf ("%e \t", CurrCoord[j][i]);
        printf("\n");
    }
    printf("\n\n");
}

bool Subspace_Iteration::equal() const{
    double coef;
    std::vector<double> res(vector_size, 0);

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            coef = scalar_product(CurrCoord[j], PrevCoord[i]);
            for (size_t k = 0; k < vector_size; ++k) {
                res[k] += CurrCoord[j][k] * coef;
            }
        }
        for (size_t k = 0; k < vector_size; ++k) {
            if (res[k] - PrevCoord[i][k] < EPS) continue;
            else return false;
        }
        res.clear();
        res.resize(vector_size,0);
    }

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            coef = scalar_product(CurrCoord[i], PrevCoord[j]);
            for (size_t k = 0; k < vector_size; ++k) {
                res[k] += PrevCoord[j][k] * coef;
            }
        }
        for (size_t k = 0; k < vector_size; ++k) {
            if (res[k] - CurrCoord[i][k] < EPS) continue;
            else return false;
        }
        res.clear();
        res.resize(vector_size,0);
    }

    return true;
}

void Subspace_Iteration::initial_value() {
    std::mt19937 gen(time(0));
    std::uniform_real_distribution<> urd(-10,10);
    size_t coordnum, vectornum;   //the number of coordinates of the vector, the number of vector


    for (vectornum = 0; vectornum < size; ++vectornum)
        for (coordnum = 0; coordnum < vector_size; ++coordnum)
            CurrCoord[vectornum][coordnum] = urd(gen);

    print();

    Orthogonalization();

    print();
}
