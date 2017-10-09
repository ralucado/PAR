/*
 * Compute pi by approximating the area under the curve f(x) = 4 / (1 + x*x)
 * between 0 and 1.
 *
 * parallel version using OpenMP
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "constants.h"
#include <omp.h>	/* OpenMP */

double getusec_() {
        struct timeval time;
        gettimeofday(&time, 0);
        return ((double)time.tv_sec * (double)1e6 + (double)time.tv_usec);
}


int main(int argc, char *argv[]) {

    double x, sum=0.0, pi=0.0;
    double stamp;
    double step;
    int i;

    const char Usage[] = "Usage: pi <num_steps> (try 1000000000)\n";
    if (argc < 2) {
	fprintf(stderr, Usage);
	exit(1);
    }
    int num_steps = atoi(argv[1]);
    step = 1.0/(double) num_steps;

    START_COUNT_TIME;



    /* do computation -- using all available threads */
    #pragma omp parallel
    {

        #pragma omp for private(x)
        for (i=0; i < num_steps; ++i) {
            x = (i+0.5)*step;
            #pragma omp critical 
            sum += 4.0/(1.0+x*x);
        }
    }
    pi = step * sum;

    STOP_COUNT_TIME("Pi Computation ");

    /* print results */
    printf("pi = %12.10f\n", pi);


    return EXIT_SUCCESS;
}
