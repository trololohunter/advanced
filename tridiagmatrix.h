//
// Created by vover on 11/12/18.
//

#ifndef ADVANCED_TRIDIAGMATRIX_H
#define ADVANCED_TRIDIAGMATRIX_H

#include <vector>
#include <cstdlib>

class tridiagmatrix {

    std::vector<double> a;
    std::vector<double> b;
    std::vector<double> c;
    int n;

public:
    tridiagmatrix();
    ~tridiagmatrix();
    tridiagmatrix(int m);
    void resize(int m);
    int solver (std::vector<double> &rhs, std::vector<double> &x);
    std::vector<double> multiply_vector (const std::vector<double> &v);
    int Add_El (size_t i, size_t j, double data);

    friend class Subspace_Iteration;
};


#endif //ADVANCED_TRIDIAGMATRIX_H
