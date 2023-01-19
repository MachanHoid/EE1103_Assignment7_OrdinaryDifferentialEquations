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

void heun(double *x, double *y, double dx){
    double ye = *y + f(*x, *y)*dx;
    double slope = (f(*x, *y) + f(*x + dx, ye))/2;
    *y += slope*dx;
    *x += dx;
}

void midpoint(double *x, double *y, double dx){
    double ym = *y + f(*x, *y)*(dx/2);
    *y += f(*x + dx/2, ym)*dx;
    *x += dx;
}

//integrator
void integrator(double yi, double xi, double xf, double dx, void (*updater_func)(double *x, double *y, double dx), FILE* fp){
    double x,y;
    x = xi;
    y = yi;
    fprintf(fp, "%lf    %lf\n", x, y);
    while(x<xf){
        updater_func(&x, &y, dx);
        fprintf(fp, "%lf    %lf\n", x, y);
    }
}



void main(){
    double yi, xi, xf, dx;
    yi = 0;
    xi = 0;
    xf = 2;
    dx = 0.1;

    FILE* fp_euler = fopen("euler_solution.txt", "w");
    integrator(yi, xi, xf, dx, &euler, fp_euler);

    FILE* fp_heun = fopen("heun_solution.txt", "w");
    integrator(yi, xi, xf, dx, &heun, fp_heun);

    FILE* fp_midpoint = fopen("midpoint_solution.txt", "w");
    integrator(yi, xi, xf, dx, &midpoint, fp_midpoint);
}