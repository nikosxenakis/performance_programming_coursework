SRC=MD.c control.c util.c 
OBJ=$(SRC:.c=.o)
OBJ_ASSEMBLY=$(SRC:.c=.s)
CC=icc 
# INIT_FLAGS=-g -O0 -check=uninit -check-pointers:rw -no-vec
CFLAGS=-Wall -Winline
VALGRIND_FLAGS= -g
PERFORMANCE_FLAGS= -O3
ASSEMBLY_FLAGS= -S
GPROF= -pg

#CHECK: -axcode

all: MD

MD: $(OBJ)
	$(CC) $(PERFORMANCE_FLAGS) -o $@ $(OBJ) -lm

MD_valgrind:
	icc $(VALGRIND_FLAGS) $(CFLAGS) -c -o MD.o MD.c
	icc $(VALGRIND_FLAGS) $(CFLAGS) -c -o control.o control.c
	icc $(VALGRIND_FLAGS) $(CFLAGS) -c -o util.o util.c
	icc $(VALGRIND_FLAGS) $(CFLAGS) -o $@ MD.o control.o util.o -lm

MD_gprof:
	icc $(GPROF) -c -o MD.o MD.c
	icc $(GPROF) -c -o control.o control.c
	icc $(GPROF) -c -o util.o util.c
	icc $(GPROF) -o $@ MD.o control.o util.o -lm

MD_assembly:
	$(CC) $(ASSEMBLY) -o MD.s MD.c

output.dat: MD input.dat
	./MD

clean:
	rm -f MD $(OBJ) 

$(OBJ) : coord.h Makefile


# valgrind --tool=cachegrind --cachegrind-out-file=cachegrind_output.txt ./MD_valgrind
# cg_annotate --auto=yes cachegrind_output.txt
