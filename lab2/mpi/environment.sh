#!/bin/bash

export EXTRAE_HOME=/assig/par/extrae/installation/
export PAPI_HOME=/assig/par/papi/installation/
export MPI_HOME=/assig/par/mpi/installation/
export PARAVER_HOME=/assig/par/paraver/installation/
export XML2_HOME=/assig/par/xml2/installation/
export HOME_XML2=/assig/par/xml2/installation/
export FFTW3_HOME=/assig/par/fftw3/installation/
export EXTRAE_CONFIG_FILE=${EXTRAE_HOME}/share/example/MPI/extrae.xml
export PATH=/usr/bin/:${EXTRAE_HOME}/bin/:${MPI_HOME}/bin/:${PARAVER_HOME}/bin/:$PATH
export LD_LIBRARY_PATH=${EXTRAE_HOME}/lib:${MPI_HOME}/lib:${XML2_HOME}/lib/:${FFTW3_HOME}/lib
#source ${EXTRAE_HOME}/etc/extrae.sh

