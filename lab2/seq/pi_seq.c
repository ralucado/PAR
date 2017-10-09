/*
 * Compute pi by approximating the area under the curve f(x) = 4 / (1 + x*x)
 * between 0 and 1.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "constants.h"
#include "extrae_user_events.h"

double getusec_() {
        struct timeval time;
        gettimeofday(&time, 0);
        return ((double)time.tv_sec * (double)1e6 + (double)time.tv_usec);
}

int main(int argc, char *argv[]) {

    Extrae_init();

    // Start REST_MAIN
    double x, sum=0.0, pi=0.0;
    double stamp;
    int i;


    const char Usage[] = "Usage: pi <num_steps> (try 1000000000)\n";
    if (argc < 2) {
	fprintf(stderr, Usage);
	exit(1);
    }
    int num_steps = atoi(argv[1]);
    // End REST_MAIN

    // Start TIMING
    START_COUNT_TIME;
    // End TIMING

    // Start PI_COMPUTATION
    double step = 1.0/(double) num_steps;

        for (i=0; i < num_steps; ++i) {
            x = (i+0.5)*step;
            sum += 4.0/(1.0+x*x);
        }
            pi = step * sum;

    // End PI_COMPUTATION

    // Start TIMING
    STOP_COUNT_TIME("Pi Computation ");
    // End TIMING

    // Start REST_MAIN
    /* print results */
    printf("pi = %12.10f\n", pi);
    // End REST_MAIN 

    Extrae_fini();

    return EXIT_SUCCESS;
}
