#!/bin/bash

USAGE="\n USAGE: run-seq.sh PROG size\n
        PROG    -> sequential program name \n
	size    -> size of the problem\n"

#Parameters
if (test $# -lt 2 || test $# -gt 2)
then
	echo -e $USAGE
	exit 0					
fi		

export EXTRAE_LABELS=./user-events.dat

/usr/bin/time ./$1 $2

mpi2prv -f TRACE.mpits -o $1_$2.prv -e $1 -paraver
