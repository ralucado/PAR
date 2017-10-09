#include "mpi.h" 
#include <stdio.h> 
#include <math.h> 
#include <stdlib.h>
#include <sys/time.h>
#include "constants.h"

#ifndef _COLLECTIVES_
  #define _COLLECTIVES_ 0
#else
  #define _COLLECTIVES_ 1
#endif 


double getusec_() {
        struct timeval time;
        gettimeofday(&time, 0);
        return ((double)time.tv_sec * (double)1e6 + (double)time.tv_usec);
}


int main( int argc, char *argv[] ) 
{ 
    int  myid, numprocs, i; 
    double step;
    double stamp;
    double mypi, pi, sum=0.0, x;

#if !_COLLECTIVES_
    MPI_Status status;
#endif
 
    MPI_Init(&argc, &argv); 
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs); 
    MPI_Comm_rank(MPI_COMM_WORLD, &myid); 

    const char Usage[] = "Usage: pi <num_steps> (try 1000000000)\n";
    if (argc < 2) {
	fprintf(stderr, Usage);
	exit(1);
    }

    int num_steps = atoi(argv[1]);
    step = 1.0 / (double) num_steps; 

    START_COUNT_TIME;

/* master broadcasts initial value of sum, a little bit artificial :) */
#if _COLLECTIVES_
    MPI_Bcast(&sum, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
#else
    if (myid == 0)
            for (i=1; i<numprocs; i++) 
                    MPI_Send(&sum, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
    else
                    MPI_Recv(&sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
#endif

    for (i = myid; i < num_steps; i += numprocs) { 
      x = (i + 0.5)*step; 
      sum += (4.0 / (1.0 + x*x)); 
    } 
    mypi = step * sum;
 
    /* master collects all partial sums */
#if _COLLECTIVES_
    MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD); 
#else
    if (myid == 0) {
            pi = mypi;
            for (i=1; i<numprocs; i++) {
                    MPI_Recv(&mypi, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
                    pi += mypi;
            }
    }
    else 
            MPI_Send(&mypi, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
#endif
 
    STOP_COUNT_TIME("Pi Computation ");

    /* master prints the answer */
    if (myid == 0)  
         printf("pi = %12.10f\n", pi);

    MPI_Finalize(); 
    return 0; 
} 
