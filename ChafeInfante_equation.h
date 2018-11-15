//
// Created by vover on 11/14/18.
//

#ifndef ADVANCED_CHAFIINFANTE_EQUATION_H
#define ADVANCED_CHAFIINFANTE_EQUATION_H


#include <vector>
#include <cstdlib>
#include "tridiagmatrix.h"

class ChafeInfante_equation {
private:
    double b;
    double a;
    int p = 1;
    size_t vector_size;

    std::vector<double> u;
    std::vector<double> Su;
    std::vector<double> Lu;
    std::vector<double> Ru;
    std::vector<double> Pp;
    std::vector<double> Pm;

public:

    ChafeInfante_equation() {};
    ~ChafeInfante_equation() {};

    void new_ab (double a, double b);
    void resize(size_t n);
    double Get_ui (int i);

    void S ();
    void L ();
    void R ();
    void Pplus ();
    void Pminus ();
};


#endif //ADVANCED_CHAFIINFANTE_EQUATION_H
