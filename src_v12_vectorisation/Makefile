SRC=MD.c control.c
OBJ=$(SRC:.c=.o)

GCC= gcc
ICC= icc

INITIAL_FLAGS=-g -O0 #-check=uninit -check-pointers:rw -no-vec

CFLAGS= -g -Wall -Winline -pg -restrict -qopenmp-simd
OPTIMISATION_FLAGS= -Ofast
ICC_FLAGS= -ipo  -xBROADWELL #  -march=core-avx2 # -axCORE-AVX2

# GCC_FLAGS= -fdump-tree-vect-all=report_gcc.txt -fopt-info -fopt-info-missed=missed.all -fopt-info-loop-optimized

%.o: %.c
	$(ICC) $(CFLAGS) $(DEBUG_FLAGS) $(OPTIMISATION_FLAGS) $(ICC_FLAGS) -c $< -o $@

MD: $(OBJ)
	$(ICC) $(CFLAGS) $(DEBUG_FLAGS) $(OPTIMISATION_FLAGS) $(ICC_FLAGS) -qopt-report-file=report_icc.txt -qopt-report=5 -o $@ $(OBJ) -lm

# %.o: %.c
# 	$(ICC) $(CFLAGS) $(DEBUG_FLAGS) $(OPTIMISATION_FLAGS) $(GCC_FLAGS) -c $< -o $@

# MD_gcc:
# 	make $(OBJ)
# 	$(GCC) $(CFLAGS) $(DEBUG_FLAGS) $(OPTIMISATION_FLAGS) $(GCC_FLAGS) -o $@ $(OBJ) -lm

run: MD
	./MD

clean:
	rm -f MD $(OBJ)

.PHONY: MD run
