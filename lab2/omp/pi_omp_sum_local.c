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
#include "extrae_user_events.h"
#include <omp.h>	/* OpenMP */

double getusec_() {
        struct timeval time;
        gettimeofday(&time, 0);
        return ((double)time.tv_sec * (double)1e6 + (double)time.tv_usec);
}


int main(int argc, char *argv[]) {

    double x, sum=0.0, pi=0.0;
    double sum_local = 0.0;
    double step;
    double stamp;
    int i;

    Extrae_init();
    Extrae_event (PROGRAM, REST_MAIN);
    const char Usage[] = "Usage: pi <num_steps> (try 1000000000)\n";
    if (argc < 2) {
	fprintf(stderr, Usage);
	exit(1);
    }
    int num_steps = atoi(argv[1]);
    step = 1.0/(double) num_steps;
    Extrae_event (PROGRAM, END);

    Extrae_event (PROGRAM, TIMING);
    START_COUNT_TIME;
    Extrae_event (PROGRAM, END);



    /* do computation -- using all available threads */
    #pragma omp parallel private(sum_local)
    {
        Extrae_event (PROGRAM, PI_COMPUTATION);
        sum_local = 0.0;

        #pragma omp for private(x)
        for (i=0; i < num_steps; ++i) {

            x = (i+0.5)*step;
            sum_local += 4.0/(1.0+x*x);
        }
        #pragma omp critical
            sum += sum_local;

        Extrae_event (PROGRAM, END);
    }

    Extrae_event (PROGRAM, PI_COMPUTATION);
    pi = step * sum;
    Extrae_event (PROGRAM, END);

    Extrae_event (PROGRAM, TIMING);
    STOP_COUNT_TIME("Pi Computation ");
    Extrae_event (PROGRAM, END);

    Extrae_event (PROGRAM, REST_MAIN);
    /* print results */
    printf("pi = %12.10f\n", pi);
    Extrae_event (PROGRAM, END);

    Extrae_fini();

    return EXIT_SUCCESS;
}
