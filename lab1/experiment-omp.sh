#!/bin/bash



USAGE="\n USAGE: experiment.sh PROG size np_MIN np_NMAX [n_exec]\n
        PROG    -> omp program name\n
	size    -> size of the problem\n
	np_NMIN -> lower bound of number of threads to be used\n
	np_NMAX -> upper bound of number of threads to be used\n
     Optional:\n
        n_exec  -> number of executions\n"


#Parameters
if (test $# -lt 4 || test $# -gt 5)
then
	echo -e $USAGE
	exit 0					
fi		

PROG=$1 # Program name, tambien se podria poner como parametro
size=$2
np_NMIN=$3
np_NMAX=$4
N=$5

if [ "$5" = "" ]
then
     N=5     # Number of times to run the program                 
fi

echo $PROG $size $np_NMIN $np_NMAX $N


out=/tmp/out.$$		# Temporal file where you save the execution results
aux=/tmp/aux.$$     # archivo auxiliar

outputpath=/tmp/experout
outputpathb=/tmp/experoutb
rm $outputpath 2> /dev/null
rm $outputpathb 2> /dev/null

i=0

PARS=$np_NMIN
while (test $PARS -le $np_NMAX)
do

	echo Executing $PROG with $PARS threads 
		elapsed=0  # Acumulacion del elapsed time de las N ejecuciones del programa

		while (test $i -lt $N)
		do
			echo -n Run $i... 
                        export OMP_NUM_THREADS=$PARS
			/usr/bin/time --format=%e ./$PROG $size > $out 2>$aux

			time=`cat $aux|tail -n 1`
			echo Elapsed time = `cat $aux`
			
			elapsed=`echo $elapsed + $time|bc`
			
			rm -f $out
			rm -f $aux
			i=`expr $i + 1`
		done

	echo -n ELAPSED TIME AVERAGE OF $N EXECUTIONS =

    result=`echo $elapsed/$N|bc -l`
    echo $result
	echo
	i=0

    #output PARS i average en un fichero
	echo -n $PARS >> $outputpath
	echo -n "   " >> $outputpath
    echo $result >> $outputpath

    #incrementa el parametre
	PARS=`expr $PARS + 1`

	
done

echo "Resultat de l'experiment (tambe es troba a " $outputpath " )"
echo "#decimals	Elapsed average"
cat $outputpath
echo

./jgraph -P grafica-omp.jgr > grafica-omp.ps
gs grafica-omp.ps



