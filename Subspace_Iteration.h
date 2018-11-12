//
// Created by vover on 10/24/18.
//

#ifndef ADVANCED_SUBSPACE_ITERATION_H
#define ADVANCED_SUBSPACE_ITERATION_H


#include <cstdint>
#include <vector>
#include <cstdio>


class Subspace_Iteration {

    size_t  size = 0;
    size_t vector_size = 0;

    std::vector<std::vector<double>> CurrCoord;
    std::vector<std::vector<double>> PrevCoord;

public:
    Subspace_Iteration() {};
    ~Subspace_Iteration() {};

    void initial_value ();
    void resize(size_t m, size_t n);
    void Orthogonalization ();
    void print() const;
    bool equal() const;
};


#endif //ADVANCED_SUBSPACE_ITERATION_H
