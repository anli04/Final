ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: game.o funcs.o
	$(CC) -o game game.o funcs.o

game.o: game.c funcs.h
	$(CC) -c game.c

funcs.o: game.c funcs.h
	$(CC) -c game.c

run:
	./game

memcheck:
	valgrind --leak-check=yes ./game

clean:
	rm *.o
	rm *~
