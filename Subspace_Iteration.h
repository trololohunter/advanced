//
// Created by vover on 10/24/18.
//

#ifndef ADVANCED_SUBSPACE_ITERATION_H
#define ADVANCED_SUBSPACE_ITERATION_H


#include <cstdint>
#include <vector>

class Subspace_Iteration {
public:
    uint8_t  size;
    uint64_t vector_size;

    std::vector<std::vector<double>> Coordinate;

    Subspace_Iteration();
    ~Subspace_Iteration();

    void Sub_Iter_resize(uint8_t m, uint64_t n);
    void Orthogonalization ();
};


#endif //ADVANCED_SUBSPACE_ITERATION_H
