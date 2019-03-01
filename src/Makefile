SRC=MD.c control.c
OBJ=$(SRC:.c=.o)
OBJ_ASSEMBLY=$(SRC:.c=.s)
CC= icc # gcc 
INITIAL_FLAGS=-g -O0 -check=uninit -check-pointers:rw -no-vec
CFLAGS= -Wall -Winline # -unroll=0
# PERFORMANCE_FLAGS= -O3
ASSEMBLY_FLAGS= -g -S -fsource-asm -c
VALGIRIND= -g
GPROF= -pg
EXE = MD


all: $(EXE)

MD: $(OBJ)
	$(CC) $(CFLAGS) $(PERFORMANCE_FLAGS) -o $@ $(OBJ) -lm

MD_valgrind:
	$(CC) $(CFLAGS) $(VALGIRIND) -c -o MD.o MD.c
	$(CC) $(CFLAGS) $(VALGIRIND) -c -o control.o control.c
	$(CC) $(CFLAGS) $(VALGIRIND) -c -o util.o util.c
	$(CC) $(CFLAGS) $(VALGIRIND) -o $@ MD.o control.o util.o -lm

MD_gprof:
	$(CC) $(GPROF) -c -o MD.o MD.c
	$(CC) $(GPROF) -c -o control.o control.c
	$(CC) $(GPROF) -c -o util.o util.c
	$(CC) $(GPROF) -o $@ MD.o control.o util.o -lm

assembly:
	$(CC) $(CFLAGS) $(ASSEMBLY_FLAGS) MD.c

output.dat: $(EXE) input.dat
	./$(EXE)

clean:
	rm -f $(EXE) $(OBJ) $(OBJ_ASSEMBLY)

$(OBJ) : coord.h Makefile
