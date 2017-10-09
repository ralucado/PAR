CC = gcc

CINCL    = -I${EXTRAE_HOME}/include/ -I.
CFLAGS   = -Wall -O3 -fopenmp -fno-inline -march=native $(CINCL)
CLIBS = -L$(EXTRAE_HOME)/lib -lomptrace -lxml2 

TARGETS= pi_omp_critical pi_omp_sum_local 

all: $(TARGETS) 

pi_omp_critical: pi_omp_critical.c
	$(CC) $< $(CFLAGS) -o $@ $(CLIBS)

pi_omp_sum_local: pi_omp_sum_local.c
	$(CC) $< $(CFLAGS) -o $@ $(CLIBS)

clean:
	rm -rf TRACE*.mpit $(TARGETS) *.prv *.pcf *.row set-0 *.mpits

