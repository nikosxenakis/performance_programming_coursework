SRC=MD.c control.c util.c 
OBJ=$(SRC:.c=.o)
OBJ_ASSEMBLY=$(SRC:.c=.s)
CC=icc 
# CFLAGS= -g -O0 -check=uninit -check-pointers:rw -no-vec
PERFORMANCE_FLAGS= -g0 -O3
# ASSEMBLY= -S

all: MD

MD: $(OBJ)
	$(CC) $(CFLAGS) $(PERFORMANCE_FLAGS) -o $@ $(OBJ) -lm

MD_ASSEMBLY:
	$(CC) $(ASSEMBLY) -o MD.s MD.c

output.dat: MD input.dat
	./MD

clean:
	rm -f MD $(OBJ) 

$(OBJ) : coord.h Makefile


