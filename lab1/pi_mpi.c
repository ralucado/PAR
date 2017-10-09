#include "mpi.h" 
#include <stdio.h> 
#include <math.h> 
#include <stdlib.h>
#include <sys/time.h>
#include "constants.h"

double getusec_() {
        struct timeval time;
        gettimeofday(&time, 0);
        return ((double)time.tv_sec * (double)1e6 + (double)time.tv_usec);
}


int main( int argc, char *argv[] ) 
{ 
    int  myid, numprocs, i; 
    double stamp;
    double mypi, pi, sum, x; 
    MPI_Init(&argc,&argv); 
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs); 
    MPI_Comm_rank(MPI_COMM_WORLD,&myid); 

    const char Usage[] = "Usage: pi <num_steps> (try 1000000000)\n";
    if (argc < 2) {
	fprintf(stderr, Usage);
	exit(1);
    }

    int num_steps = atoi(argv[1]);

    START_COUNT_TIME;
    double   step = 1.0 / (double) num_steps; 

    sum = 0.0; 
    for (i = myid; i < num_steps; i += numprocs) { 
      x = (i + 0.5)*step; 
      sum += (4.0 / (1.0 + x*x)); 
    } 

    mypi = step * sum; 
    MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD); 
    STOP_COUNT_TIME("Pi Computation ");
    if (myid == 0)  
         printf("pi = %12.10f\n", pi);

    MPI_Finalize(); 
    return 0; 
} 
