#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ode_methods.c"

//dy/dx = deriv(x, y)
double deriv(double x, double y){
    return -100000*y + 99999*exp(-x);
}

//implicit euler method
void prob2_implicit_euler(double *x, double *y, double dx, double (*deriv_func)(double x, double y)){
    *x += dx;
    *y = (*y + 99999*dx*exp(- *x))/(1 + 100000*dx);
}

void main(){
    //Problem 2
    //(a) Explicit Euler
    double yi, xi, xf, dx;
    yi = 0;
    xi = 0;
    xf = 2;

    //using h = 2 e-5 (boundary case for stability)
    dx = 0.00002;
    FILE* fp_explicit_euler1 = fopen("p2a_1_soln.txt", "w");
    integrator(yi, xi, xf, dx, &euler, &deriv, fp_explicit_euler1);

    //using h = 0.5 e-5 (stable case)
    dx = 0.000005;
    FILE* fp_explicit_euler2 = fopen("p2a_2_soln.txt", "w");
    integrator(yi, xi, xf, dx, &euler, &deriv, fp_explicit_euler2);

    //using h = 2.1 e-5 (unstable case)
    dx = 0.000021;
    FILE* fp_explicit_euler3 = fopen("p2a_3_soln.txt", "w");
    integrator(yi, xi, xf, dx, &euler, &deriv, fp_explicit_euler3);


    //(b) Implicit Euler
    dx = 0.1;
    FILE* fp_implicit_euler = fopen("p2b_soln.txt", "w");
    integrator(yi, xi, xf, dx, &prob2_implicit_euler, &deriv, fp_implicit_euler);
}