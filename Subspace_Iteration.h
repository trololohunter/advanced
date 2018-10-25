//
// Created by vover on 10/24/18.
//

#ifndef ADVANCED_SUBSPACE_ITERATION_H
#define ADVANCED_SUBSPACE_ITERATION_H


#include <cstdint>
#include <vector>
#include <cstdio>

class Subspace_Iteration {
public:
    size_t  size;
    size_t vector_size;

    std::vector<std::vector<double>> Coordinate;

    Subspace_Iteration() {};
    ~Subspace_Iteration() {};

    void resize(size_t m, size_t n);
    void Orthogonalization ();
    void print() const;
    friend bool equal (const Subspace_Iteration &A, const Subspace_Iteration &B);
};


#endif //ADVANCED_SUBSPACE_ITERATION_H
