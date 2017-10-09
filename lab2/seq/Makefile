CC = gcc
CINCL    = -I${EXTRAE_HOME}/include/ -I.
CFLAGS   = -Wall -O3 -fno-inline -march=native $(CINCL)
CLIBS    = -L$(EXTRAE_HOME)/lib -lseqtrace -lxml2

TARGETS  = pi_seq 
program:	$(TARGETS)

pi_seq: pi_seq.c
	$(CC) $(CFLAGS) $< -o $@ $(CLIBS)

clean:
	rm -fr TRACE*.mpit* $(TARGETS) set-0 *.row *.pcf *.prv

