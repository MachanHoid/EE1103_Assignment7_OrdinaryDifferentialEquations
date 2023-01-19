#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//dy/dx = f(x, y)
double f(double x, double y){
    return 2*x;
}

//methods
void euler(double *x, double *y, double dx){
    *y += f(*x,*y)*dx;
    *x += dx;
}

//integrator
void integrator(double yi, double xi, double xf, double dx, void (*updater_func)(double *x, double *y, double dx), FILE* fp){
    double x,y;
    x = xi;
    y = yi;
    fprintf(fp, "%lf    %lf\n", x, y);
    while(x<=xf){
        updater_func(&x, &y, dx);
        fprintf(fp, "%lf    %lf\n", x, y);
    }
}



void main(){
    FILE* fpointer = fopen("euler_solution.txt", "w");
    double yi, xi, xf, dx;
    yi = 0;
    xi = 0;
    xf = 2;
    dx = 0.01;

    integrator(yi, xi, xf, dx, &euler, fpointer);
}