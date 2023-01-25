#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//methods
void euler(double *x, double *y, double dx, double (*deriv_func)(double x, double y)){
    *y += deriv_func(*x,*y)*dx;
    *x += dx;
}

void heun(double *x, double *y, double dx, double (*deriv_func)(double x, double y)){
    double ye = *y + deriv_func(*x, *y)*dx;
    double slope = (deriv_func(*x, *y) + deriv_func(*x + dx, ye))/2;
    *y += slope*dx;
    *x += dx;
}

void midpoint(double *x, double *y, double dx, double (*deriv_func)(double x, double y)){
    double ym = *y + deriv_func(*x, *y)*(dx/2);
    *y += deriv_func(*x + dx/2, ym)*dx;
    *x += dx;
}

void rungeKutta4(double *x, double *y, double dx, double (*deriv_func)(double x, double y)){
    double k1, k2, k3, k4;
    k1 = deriv_func(*x, *y);
    k2 = deriv_func(*x + dx/2, *y + k1 * (dx/2));
    k3 = deriv_func(*x + dx/2, *y + k2 * (dx/2));
    k4 = deriv_func(*x + dx, *y + k3 * dx);
    
    *y += ((k1 + 2*k2 + 2*k3 + k4)*dx)/6;
    *x += dx;
}

//integrator
void integrator(double yi, double xi, double xf, double dx, void (*updater_func)(double *x, double *y, double dx, double (*deriv_func)(double x, double y)), double (*deriv_func)(double x, double y), FILE* fp){
    double x,y;
    x = xi;
    y = yi;
    fprintf(fp, "%lf    %lf\n", x, y);
    while(x<xf){
        updater_func(&x, &y, dx, deriv_func);
        fprintf(fp, "%lf    %lf\n", x, y);
    }
}