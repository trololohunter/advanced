//
// Created by vover on 11/14/18.
//

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "ChafeInfante_equation.h"
#include "math_vector.h"

#define C_2 0.1
#define CONST 5

double coef(const std::vector<double> &v, int i, double h);

template <typename T>
std::string toString(T val)
{
    std::ostringstream oss;
    oss<< val;
    return oss.str();
}

double cube (double x) {
    return x*x;
}

void ChafeInfante_equation::resize(size_t n) {
    vector_size = n+1;
    data.N = n;
    data.h = (data.b - data.a)/n;
    u_prev.resize(n+1);
    u_curr.resize(n+1);
    Ru.resize(n+1);
    Lu.resize(n+1);
    Su.resize(n+1);
    Pp.resize(n+1);
    Pm.resize(n+1);
}


void ChafeInfante_equation::S() {
    tridiagmatrix matr;
    std::vector<double> x;
    std::vector<double> rhs;

    matr.resize(int(vector_size-2));
    x.resize(vector_size-2);
    rhs.resize(vector_size-2);

    Fill_tridiagmatrix_S(matr, rhs);


    matr.solver(rhs, x);

    Su[0] = 0;
    for (size_t i = 1; i < vector_size-1; ++i)
        Su[i] = x[i-1];
    Su[vector_size-1] = 0;
}

void ChafeInfante_equation::L() {
    tridiagmatrix matr;
    std::vector<double> x;
    std::vector<double> rhs;

    matr.resize(int(vector_size-2));
    x.resize(vector_size-2);
    rhs.resize(vector_size-2);

    Fill_tridiagmatrix_L(matr, rhs);
    matr.solver(rhs, x);

    Lu[0] = 0;
    for (size_t i = 1; i < vector_size-1; ++i)
        Lu[i] = x[i-1];
    Lu[vector_size-1] = 0;
}

void ChafeInfante_equation::R() {

    for (size_t i = 0; i < vector_size; ++i)
        Ru[i] = Su[i] - Lu[i];
        //Ru[i] = 1e-3 * sin(i * data.h);
}

std::vector<double> Pplus(std::vector<double> v, size_t vector_size, double h, int i_zero) {
    double alpha;
    std::vector<double> rez(vector_size, 0);

    print_vector(v);
    for (size_t i = 1; i < i_zero + 1; ++i)
    {
        alpha = 0;
        for (size_t k = 0; k < vector_size; ++k)
            alpha += v[k] * sin(i * k * h);
        std::cout << alpha << std::endl;
        alpha *= 2;         // должно быть деление на скалярное произведение, но у нас оно 0.5
        for (size_t k = 0; k < vector_size; ++k)
            rez[k] += alpha * sin(i * k * h);
    }

    return rez;
}

std::vector<double> Pminus(std::vector<double> v, std::vector<double> w, size_t vector_size) {

    std::vector<double> rez(vector_size);

    for (size_t i = 0; i < vector_size; ++i)
        rez[i] = v[i] - w[i];

    return rez;
}

void ChafeInfante_equation::Fill_tridiagmatrix_S(tridiagmatrix &matr, std::vector<double> &rhs) {
    double push;

    push = 1 + 2*data.tau/(data.h * data.h) - data.beta*data.tau;
    matr.Add_El(0,0,push);
    push = -data.tau/(data.h * data.h);
    matr.Add_El(0,1,push);
    rhs[0] = u_prev[1]  + data.alpha * cube(u_prev[1]) * data.tau;

    for (size_t i = 1; i < vector_size-3; ++i)
    {
        push = 1 + 2*data.tau/(data.h * data.h) - data.beta*data.tau;
        matr.Add_El(i,i,push);
        push = -data.tau/(data.h * data.h);
        matr.Add_El(i,i+1,push);
        push = -data.tau/(data.h * data.h);
        matr.Add_El(i,i-1,push);
        rhs[i] = u_prev[i+1]  + data.alpha * cube(u_prev[i+1]) * data.tau;

    }

    push = 1 + 2*data.tau/(data.h * data.h) - data.beta*data.tau;
    matr.Add_El(vector_size-3,vector_size-3,push);
    push = -data.tau/(data.h * data.h);
    matr.Add_El(vector_size-3,vector_size-4,push);
    rhs[vector_size-3] = u_prev[vector_size-2]  + data.alpha * cube(u_prev[vector_size-2]) * data.tau;

}

void ChafeInfante_equation::Fill_tridiagmatrix_L(tridiagmatrix &matr, std::vector<double> &rhs) {
    double alpha_ = data.alpha;
    data.alpha = 0;

    Fill_tridiagmatrix_S(matr, rhs);

    data.alpha  = alpha_;
}

void ChafeInfante_equation::solver() {
    double c = 0;
    std::vector<double> v(vector_size), w(vector_size);
    double alpha, beta;
    int n_zero_prev;


    u_zero(c);

    typical_time(c);
    u_zero(c);
    for (int i = 0; i < data.n_zero; ++i)
    {
        u_prev = u_curr;
        L();
        u_curr = Lu;
    }

    R();

    for (int i = 0; i < vector_size; ++i)
        u_curr[i] = u_prev[i] = sin(i * data.h);

    for (int i = 0; i < data.n_zero; ++i)
    {
        u_prev = u_curr;
        L();
        u_curr = Lu;
    }

    //print_vector(Lu);
    //print_vector(Ru);
    alpha = coef(Pplus(Lu, vector_size, data.h, i_zero), 1, data.h);
    beta = -coef(Pplus(Ru, vector_size, data.h, i_zero), 1, data.h);

    std::ofstream fout;
    fout.open("file");
    u_zero(0);
    for (int i = 1; i < vector_size-1; ++i)
        fout << u_curr[i] << '\t' << Lu[i] << '\t' << u_curr[i]/Lu[i] << std::endl;
    fout.close();

    c = beta / alpha;
    std::cout << "КОЭФФИЦИЕНТ === " << c << std::endl;
    std::cout << alpha << '\t' << beta <<std::endl;
    n_zero_prev = data.n_zero;

    u_zero(c);
    typical_time(c);

    while (n_zero_prev < data.n_zero)
    {
        u_zero(c);
        for (int i = 0; i < data.n_zero; ++i)
        {
            u_prev = u_curr;
            L();
            u_curr = Lu;
        }

        R();

        for (int i = 0; i < vector_size; ++i)
            u_curr[i] = u_prev[i] = sin(i * data.h);

        for (int i = 0; i < data.n_zero; ++i)
        {
            u_prev = u_curr;
            L();
            u_curr = Lu;
        }

        alpha = coef(Pplus(Lu, vector_size, data.h, i_zero), 1, data.h);
        beta = -coef(Pplus(Ru, vector_size, data.h, i_zero), 1, data.h);
        std::cout << alpha << '\t' << beta << std::endl;

        c = beta / alpha;

        n_zero_prev = data.n_zero;

        u_zero(c);
        typical_time(c);
    }


}

void ChafeInfante_equation::u_zero(double C) {
    u_curr[0] = u_prev[0] = 0;
    u_curr[vector_size-1] = u_prev[vector_size-1] = 0;
    for (size_t i = 1; i < vector_size-1; ++i)
        u_curr[i] = u_prev[i] = C_2 * sin(2 * data.h * i) + C * sin (data.h * i);
}

void ChafeInfante_equation::typical_time(double C) {
    double norm_curr, norm_prev;
    std::string filename;
    std::vector<double> v(vector_size), w(vector_size);
    std::ofstream fout;

    filename = "withcravno" + toString(C);

    fout.open(filename);


    u_zero(C);
    //print_vector(u_curr);
    norm_prev = norm(u_curr);
    fout << 0 << '\t' << norm_prev << std::endl;
    S(); // один шаг схемы
    //print_vector(Su);
    norm_curr = norm(Su);
    u_curr = Su;
    data.n_zero = 1;
    fout << data.tau << '\t' << norm_curr << std::endl;
/*
    for (int i = 0; i < CONST-3; ++i){
        u_prev = u_curr;
        S();
        norm_curr = norm(Su);
        u_curr = Su;
        fout << data.tau * ++data.n_zero << '\t' << norm_curr << std::endl;
        //fprintf (fp, "%e \t %e \n", data.tau * ++data.n_zero, norm_curr);
    }
*/
    while (norm_curr < norm_prev) {
        norm_prev = norm_curr;
        u_prev = u_curr;
        S();
        //print_vector(Su);
        norm_curr = norm(Su);
        u_curr = Su;
        //print_vector(u_curr);
        fout << data.tau * ++data.n_zero << '\t' << norm_curr << std::endl;
        //fprintf (fp, "%e \t %e \n", data.tau * ++data.n_zero, norm_curr);

        if (norm_curr < 1e-100) exit (100);
    }

    v = u_prev;

    for (int i = 0; i < CONST; ++i){
        u_prev = u_curr;
        S();
        norm_curr = norm(Su);
        u_curr = Su;
        fout << data.tau * ++data.n_zero << '\t' << norm_curr << std::endl;
        //fprintf (fp, "%e \t %e \n", data.tau * ++data.n_zero, norm_curr);
    }
    data.n_zero -= CONST;
    //data.n_zero = 5;
    Su = v;
    fout.close();
}



double coef(const std::vector<double> &v, int i, double h) {
    double rez;

    std::vector<double> sini(v.size());

    print_vector(v);
    for (int k = 0; k < v.size(); ++k)
        sini [k] = sin(i * k * h);

    rez = 2 * scalar_product(v, sini);

    return rez;
}

