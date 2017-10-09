MPICC    = mpicc
CINCL    = -I${EXTRAE_HOME}/include/ -I.
CFLAGS   = -Wall -O3 -fno-inline -march=native $(CINCL)
CLIBS    = -L$(EXTRAE_HOME)/lib -lmpitrace -lxml2 

TARGETS = pi_mpi_collectives pi_mpi

all: $(TARGETS)

pi_mpi_collectives: pi_mpi.c
	$(MPICC) $< $(CFLAGS) -D_COLLECTIVES_ $(CLIBS) -o $@

pi_mpi: pi_mpi.c
	$(MPICC) $< $(CFLAGS) $(CLIBS) -o $@

clean:
	rm -rf $(TARGETS) *.pcf *.prv *.row *.o TRACE.* set-0
