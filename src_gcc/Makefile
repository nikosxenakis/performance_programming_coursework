SRC=MD.c control.c
OBJ=$(SRC:.c=.o)

GCC= gcc

INITIAL_FLAGS=-g -O0 -check=uninit -check-pointers:rw -no-vec

CFLAGS= -g -Wall -Winline -pg -std=c99
OPTIMISATION_FLAGS= -Ofast

GCC_FLAGS= -march=core-avx2 -fdump-tree-vect-all=report_gcc.txt -fopt-info -fopt-info-loop-optimized

%.o: %.c
	$(GCC) $(CFLAGS) $(DEBUG_FLAGS) $(OPTIMISATION_FLAGS) $(GCC_FLAGS) -c $< -o $@

MD: $(OBJ)
	$(GCC) $(CFLAGS) $(DEBUG_FLAGS) $(OPTIMISATION_FLAGS) $(GCC_FLAGS) -o $@ $(OBJ) -lm

run: MD
	./MD

clean:
	rm -f MD $(OBJ)

.PHONY: MD run
