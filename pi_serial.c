#include <stdlib.h>          /* Standard Library */
#include <stdio.h>           /* IO library */
#include <math.h>            /* Math librry */
#include <omp.h>             /* OpenMP header file */
#define pi_true (acos(-1.))  /* double pi_true = 3.14159265358979323846; */

void run_serial_pi(int n, double* error, double* timer) {
    double h, x, pi = 0.;
    h = 1. / (double) n; /* Set subinterval size */
    int i;
    double time = omp_get_wtime();
    for (i = 0; i < n; i++) {   /* Perform integration */
        x = h * (i + .5);
        pi += 4.*h/(1. + x*x);
    }
    time = omp_get_wtime() - time; 
    *error += pi_true - pi;
    *timer += time;
}

int main(int argc, char* argv[]) {
    long int n = atoi(argv[1]);
    int iterations = 10, i;
    double error;
    double timer;

    for (i=0; i < iterations; i++) {
        run_serial_pi(n, &error, &timer);
    }
    error = error / iterations;
    timer = timer / iterations;

    printf("for %d iterations:\n  average error = %.16e \n   average time = %.8f seconds\n value of n = %d\n",
            iterations, error, timer, n);

    return 0; 
}
