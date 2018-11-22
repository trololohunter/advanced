//
// Created by vover on 11/14/18.
//

#ifndef ADVANCED_CHAFIINFANTE_EQUATION_H
#define ADVANCED_CHAFIINFANTE_EQUATION_H


#include <vector>
#include <cstdlib>
#include <math.h>
#include "tridiagmatrix.h"

#define DEF_N 10

struct Data {
    double mu;
    double tau;
    double h;
    size_t N;
    double a;
    double b;
    double beta;
    double alpha;
    int n_zero;
};

class ChafeInfante_equation {
private:

    int i_zero = 1;
    int p = 1;
    size_t vector_size;
    struct Data data;

    std::vector<double> u_curr;
    std::vector<double> u_prev;
    std::vector<double> Su;
    std::vector<double> Lu;
    std::vector<double> Ru;
    std::vector<double> Pp;
    std::vector<double> Pm;

public:

    ChafeInfante_equation() {
        data.a = 0;
        data.b = M_PI;
        data.N = DEF_N;
        data.tau = 0.01;
        data.h = (data.b - data.a)/data.N;
        data.beta = 3;
        data.alpha = 5;
        vector_size = data.N+1;
    };
    ~ChafeInfante_equation() {};

    void resize(size_t n);

    void Fill_tridiagmatrix_S (tridiagmatrix &matr, std::vector<double> &rhs);
    void Fill_tridiagmatrix_L (tridiagmatrix &matr, std::vector<double> &rhs);

    void S ();
    void L ();
    void R ();
    friend std::vector<double> Pplus (std::vector<double> v, size_t vector_size, double h, int i_zero);
    friend std::vector<double> Pminus (std::vector<double> v, std::vector<double> w, size_t vector_size);
    friend double coef (const std::vector<double> &v, int i, double h);

    void solver();
    void u_zero(double C);
    void typical_time (double C);
};


#endif //ADVANCED_CHAFIINFANTE_EQUATION_H
