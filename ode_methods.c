#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//dy/dx = f(x, y)
double f(double x, double y){
    return y*pow(x,3) - 1.5*y;
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

void rungeKutta4(double *x, double *y, double dx){
    double k1, k2, k3, k4;
    k1 = f(*x, *y);
    k2 = f(*x + dx/2, *y + k1 * (dx/2));
    k3 = f(*x + dx/2, *y + k2 * (dx/2));
    k4 = f(*x + dx, *y + k3 * dx);
    
    *y += ((k1 + 2*k2 + 2*k3 + k4)*dx)/6;
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
    yi = 1;
    xi = 0;
    xf = 2;
    dx = 0.1;

    FILE* fp_euler = fopen("euler_solution.txt", "w");
    integrator(yi, xi, xf, dx, &euler, fp_euler);

    FILE* fp_heun = fopen("heun_solution.txt", "w");
    integrator(yi, xi, xf, dx, &heun, fp_heun);

    FILE* fp_midpoint = fopen("midpoint_solution.txt", "w");
    integrator(yi, xi, xf, dx, &midpoint, fp_midpoint);

    FILE* fp_rk4 = fopen("rungeKutta4_solution.txt", "w");
    integrator(yi, xi, xf, dx, &rungeKutta4, fp_rk4);
}