//
// Created by vover on 11/14/18.
//

#include "ChafeInfante_equation.h"

void Fill_tridiagmatrix_S (tridiagmatrix &matr, std::vector<double> &rhs);
void Fill_tridiagmatrix_L (tridiagmatrix &matr, std::vector<double> &rhs);

void ChafeInfante_equation::resize(size_t n) {
    vector_size = n;
    u.resize(n);
    Ru.resize(n);
    Lu.resize(n);
    Su.resize(n);
    Pp.resize(n);
    Pm.resize(n);
}

void ChafeInfante_equation::new_ab(double new_a, double new_b) {
    b = new_b;
    a = new_a;
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
        Su[i] = x[i];
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

    Su[0] = 0;
    for (size_t i = 1; i < vector_size-1; ++i)
        Su[i] = x[i];
    Su[vector_size-1] = 0;
}

void ChafeInfante_equation::R() {

    for (size_t i = 0; i < vector_size; ++i)
        Ru[i] = Su[i] - Lu[i];

}

void ChafeInfante_equation::Pplus() {

}

void ChafeInfante_equation::Pminus() {

    for (size_t i = 0; i < vector_size; ++i)
        Pm[i] = u[i] - Pp[i];

}

double ChafeInfante_equation::Get_ui(int i) {
    return u[i];
}

void Fill_tridiagmatrix_S (tridiagmatrix &matr, std::vector<double> &rhs) {
    matr.Add_El(0,0,);

}
void Fill_tridiagmatrix_L (tridiagmatrix &matr, std::vector<double> &rhs) {


}