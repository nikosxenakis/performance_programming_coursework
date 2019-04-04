SRC=MD.c control.c
OBJ=$(SRC:.c=.o)

CC= clang
# CC= icc

CFLAGS= -g -Wall -Winline -pg -ffast-math
OPTIMISATION_FLAGS= -Ofast -march=broadwell -foptimization-record-file=report_clang.txt -Rpass=loop-vectorize

%.o: %.c
	$(CC) $(CFLAGS) $(OPTIMISATION_FLAGS) $(ICC_FLAGS) -c $< -o $@

MD: $(OBJ)
	$(CC) $(CFLAGS) $(OPTIMISATION_FLAGS) $(ICC_FLAGS) -o $@ $(OBJ) -lm

run: MD
	./MD

clean:
	rm -f MD $(OBJ)

.PHONY: MD run
