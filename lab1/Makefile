CC       = gcc
MPICC    = mpicc

CFLAGS   = -Wall -O3 -fno-inline -march=native

TARGET  = pi_seq pi_omp pi_mpi
OBJECTS	= $(TARGET)

program:	$(TARGET)

pi_seq: pi_seq.c
	$(CC) $< $(CFLAGS) -o $@

pi_omp: pi_omp.c
	$(CC) $< $(CFLAGS) -o $@

pi_mpi: pi_mpi.c
	$(MPICC) $< $(CFLAGS) $(CINCL) -o $@ $(CLIBS)

clean:
	rm -fr $(OBJECTS)
