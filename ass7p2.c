#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ode_methods.c"

//dy/dx = deriv(x, y)
double deriv(double x, double y){
    return -100000*y + 99999*exp(-x);
}

void main(){
    //Problem 2
    //(a)
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

    //using h = 3 e-5 (unstable case)
    dx = 0.00003;
    FILE* fp_explicit_euler3 = fopen("p2a_3_soln.txt", "w");
    integrator(yi, xi, xf, dx, &euler, &deriv, fp_explicit_euler3);


    //(b)
}