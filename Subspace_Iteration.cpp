//
// Created by vover on 10/24/18.
//

#include "Subspace_Iteration.h"

void Subspace_Iteration::Sub_Iter_resize(uint8_t m, uint64_t n) {
    size = m;
    vector_size = n;

    Coordinate.resize(m);
    for (int i = 0; i < m; ++i)
        Coordinate[i].resize(n,0);
}

void Subspace_Iteration::Orthogonalization() {


}
