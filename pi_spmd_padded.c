#include <stdlib.h>          /* Standard Library */
#include <stdio.h>           /* IO library */
#include <math.h>            /* Math librry */
#include <omp.h>             /* OpenMP header file */
#define pi_true (acos(-1.))  /* double pi_true = 3.14159265358979323846; */
#define PAD 8 /* Padding is used to ensure each sum value is contained in a separate cache line*/

void run_spmd_pi(int n, double* error, double* timer, int NUM_THREADS) {
    double h, x, pi = 0., sum[NUM_THREADS][PAD]; /* sum is an array to track the local work of each thread */
    h = 1. / (double) n; /* Set subinterval size */
    int i, nthreads;
    omp_set_num_threads(NUM_THREADS);
    double time = omp_get_wtime();

    #pragma omp parallel 
    {
        int i, id, numthrds;
        double x;
        id = omp_get_thread_num();
        numthrds = omp_get_num_threads();
        if (id == 0) nthreads = numthrds; /* Save number of threads used from only one thread. */
        for (i = id, sum[id][0] = 0.0; i < n; i += numthrds) {   /* Cyclic distribution for loop iterations */
            x = h * (i + .5);
            sum[id][0] += 4.*h/(1. + x*x);
        }
    }
    for (i = 0; i < nthreads; i++) pi += sum[i][0];
    time = omp_get_wtime() - time; 
    *error += pi_true - pi;
    *timer += time;
}

int main(int argc, char* argv[]) {
    long int n = atoi(argv[2]);
    int iterations = 10, i, nthreads;
    double error = 0.0;
    double timer = 0.0;

    for (i=0; i < iterations; i++) {
        run_spmd_pi(n, &error, &timer, atoi(argv[1]));
    }
    error = error / iterations;
    timer = timer / iterations;

    #pragma omp parallel 
    {
        int id = omp_get_thread_num();
        int numthrds = omp_get_num_threads();
        if (id == 0) nthreads = numthrds; /* Save number of threads used from only one thread. */
    }

    printf("for %d iterations:\n  average error = %.16e \n   average time = %.8f seconds\n   number thrds = %d\n   value of n = %d\n",
            iterations, error, timer, nthreads, n);

    return 0; 
}
