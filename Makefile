CC = gcc
CFLAGS = -O3 -std=c99

all: 
	$(CC) $(CFLAGS) $(OBJS) matrix_inverse.c  -o a.x
run:
	./a.x

clean:
	rm -f *.x *~ *.o
