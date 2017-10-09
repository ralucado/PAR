#!/bin/bash

USAGE="\n USAGE: run-omp.sh PROG size n_th\n
        PROG   -> omp program name\n
        size   -> total size of the problem\n
	n_th   -> number of threads\n"

if (test $# -lt 3 || test $# -gt 3)
then
	echo -e $USAGE
        exit 0
fi

export OMP_NUM_THREADS=$3
export EXTRAE_LABELS=./user-events.dat

/usr/bin/time ./$1 $2

mpi2prv -f TRACE.mpits -o $1_$2_$3.prv -e $1 -paraver
