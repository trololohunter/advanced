//
// Created by vover on 11/12/18.
//

#include "tridiagmatrix.h"

tridiagmatrix::tridiagmatrix()
{

}

tridiagmatrix::tridiagmatrix(int m)
{
    a.resize(m);
    b.resize(m-1);
    c.resize(m-1);
    n = m;
}

tridiagmatrix::~tridiagmatrix()
{
    a.clear();
    b.clear();
    c.clear();
}

void tridiagmatrix::resize(int m)
{
    a.resize(m);
    b.resize(m-1);
    c.resize(m-1);
    n = m;
}

int tridiagmatrix::solver(std::vector<double> &rhs, std::vector<double> &x)
{
    double m;
    for (int i = 1; i < n; ++i)
    {
        m = c[i-1]/a[i-1];
        a[i] -= m*b[i-1];
        rhs[i] -= m*rhs[i-1];
    }

    x[n-1] = rhs[n-1]/a[n-1];

    for (int i = n - 2; i > -1; --i)
        x[i] = (rhs[i] - b[i]*x[i+1])/a[i];

    return 0;
}

std::vector<double> tridiagmatrix::multiply_vector(const std::vector<double> &v) {
    std::vector<double> x;
    x.resize(n);

    x[0] = a[0] * v[0] + b[0] * v[1];

    for (int i = 1; i < n-1; ++i)
    {
        x[i] = a[i] * v[i] + b[i] * v[i+1] + c[i-1] * v[i-1];
    }

    x[n-1] = a[n-1] * v[n-1] + c[n-2] * v[n-2];

    return x;
}


