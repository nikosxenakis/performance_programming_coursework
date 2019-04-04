SRC=MD.c control.c
OBJ=$(SRC:.c=.o)

CC= icc

INITIAL_FLAGS=-g -O0 #-check=uninit -check-pointers:rw -no-vec

CFLAGS= -g -Wall -Winline -pg -restrict -qopenmp-simd
OPTIMISATION_FLAGS= -Ofast
ICC_FLAGS= -ipo  -xBROADWELL
REPORT_FLAGS= -qopt-report-file=report_icc.txt -qopt-report=5

#UNUSED FLAGS
GCC_FLAGS= -march=core-avx2 -fdump-tree-vect-all=report_gcc.txt -fopt-info -fopt-info-loop-optimized
SKYLAKE_FLAGS= -xSKYLAKE
LLVM_FLAGS= -march=broadwell -foptimization-record-file=report_clang.txt -Rpass=loop-vectorize

%.o: %.c
	$(CC) $(CFLAGS) $(OPTIMISATION_FLAGS) $(ICC_FLAGS) -c $< -o $@

MD: $(OBJ)
	$(CC) $(CFLAGS) $(OPTIMISATION_FLAGS) $(ICC_FLAGS) $(REPORT_FLAGS) -o $@ $(OBJ) -lm

run: MD
	./MD

clean:
	rm -f MD $(OBJ)

.PHONY: MD run
