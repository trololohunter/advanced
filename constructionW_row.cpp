//
// Created by vover on 11/7/18.
//

#include <cmath>
#include <cstdio>

#define W 1e-2
#define ITER 1000

double f(double w, double &a2, double &a3, double &a4) {
    return (a2*w*w + a3*w*w*w + a4*w*w*w*w);
}

void transformation(double &v, double &w, double &a2, double &a3, double &a4) {
    double vnew, wnew;

    vnew = 3*f(w,a2,a3,a4) + f(w,a2,a3,a4)*f(w,a2,a3,a4) + w*w;
    wnew = w/2. + 2*f(w,a2,a3,a4)*f(w,a2,a3,a4) + 3*w*w;

    w = wnew;
    v = vnew;

    return;
}

double norm(double w, double v) {
    return sqrt(w*w + v*v);
}

int func(double v, double &a2, double &a3, double &a4) {
    int n = 0;
    double norm_now, norm_prev;
    double w = W;
    int iter = 0;

    norm_now = norm(w,v);
    norm_prev = 100;

    while (norm_now - norm_prev < 1e-16) {
        transformation(v,w,a2,a3,a4);
        norm_prev = norm_now;
        norm_now = norm(w,v);
        n++;
        printf ("%e \n", norm_now - norm_prev);
        if (ITER < ++iter) break;
    }

    return n-1;
}



void rows_method () {
    double v;
    int n0, n2, n3, n4;
    double a2, a3, a4;

    a2 = -1./2.75;
    a3 = 1.5 * a2;
    a4 = (a2*a2*a2 - a2*a2 + 9*a2 + a3 * 9./4.) / 3.;

    printf ("a2 = %e \n a3 = %e \n a4 = %e \n", a2,a3,a4);

    v = 0;
    n0 = func(v,a2,a3,a4);
    printf ("v = %e \t n = %d \n", v, n0);
    v = a2 * W * W;
    n2 = func(v,a2,a3,a4);
    printf ("v = %e \t n = %d \n", v, n2);
    v +=  a3 * W * W * W;
    n3 = func(v,a2,a3,a4);
    printf ("v = %e \t n = %d \n", v, n3);
    v += a4 * W * W * W * W;
    n4 = func(v,a2,a3,a4);
    printf ("v = %e \t n = %d \n", v, n4);

    return;
}