SRC=MD.c control.c util.c 
OBJ=$(SRC:.c=.o)
CC=icc
# CFLAGS= -O3  -ipo 
CFLAGS= -fast

all: MD

MD: $(OBJ)
	$(CC) $(CFLAGS)  -o $@  $(OBJ) -lm


output.dat: MD input.dat
	./MD


clean:
	rm -f MD $(OBJ) 

$(OBJ) : coord.h Makefile


