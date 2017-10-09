#!/bin/bash

USAGE="\n USAGE: run-mpi.sh PROG size n_p\n
        PROG   -> mpi program name\n
        size   -> total size of the problem\n
        n_p    -> number of processes\n"

if (test $# -lt 3 || test $# -gt 3)
then
	echo -e $USAGE
        exit 0
fi

export EXTRAE_LABELS=./user-events.dat

## Run the desired program
mpirun -np $3 ./$1 $2

mpi2prv -f TRACE.mpits -o $1_$2_$3.prv -e $1 -paraver
