SRC=MD.c control.c
OBJ=$(SRC:.c=.o)

GCC= gcc
ICC= icc

INITIAL_FLAGS=-g -O0 -check=uninit -check-pointers:rw -no-vec

CFLAGS= -Winline -m64 -restrict
DEBUG_FLAGS= -g -Wall -pg
OPTIMISATION_FLAGS= -Ofast

ICC_FLAGS= -axCORE-AVX2 -ipo -qopenmp-simd
GCC_FLAGS= -fdump-tree-vect-all=report_gcc.txt -fopt-info -fopt-info-missed=missed.all -fopt-info-loop-optimized

%.o: %.c
	$(ICC) $(CFLAGS) $(DEBUG_FLAGS) $(OPTIMISATION_FLAGS) $(ICC_FLAGS) -c $< -o $@

MD_icc: $(OBJ)
	$(ICC) $(CFLAGS) $(DEBUG_FLAGS) $(OPTIMISATION_FLAGS) $(ICC_FLAGS) -qopt-report-file=report_icc.txt -qopt-report=5 -o $@ $(OBJ) -lm

# %.o: %.c
# 	$(ICC) $(CFLAGS) $(DEBUG_FLAGS) $(OPTIMISATION_FLAGS) $(GCC_FLAGS) -c $< -o $@

# MD_gcc:
# 	make $(OBJ)
# 	$(GCC) $(CFLAGS) $(DEBUG_FLAGS) $(OPTIMISATION_FLAGS) $(GCC_FLAGS) -o $@ $(OBJ) -lm

run_icc: MD_icc
	./MD_icc

clean:
	rm -f MD_icc MD_gcc $(OBJ)

.PHONY: MD_icc MD_gcc run_icc
