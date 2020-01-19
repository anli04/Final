ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: game.o funcs.o combat.o miniDex.o miniInt.o miniLuk.o miniSTR.o
	$(CC) -o game game.o funcs.o miniDex.o miniInt.o miniLuk.o miniSTR.o -lm
	$(CC) -o combat combat.o funcs.o -lm

game.o: game.c rpg.h
	$(CC) -c game.c

funcs.o: funcs.c rpg.h
	$(CC) -c funcs.c

combat.o: combat.c rpg.h
	$(CC) -c combat.c

miniDex.o: miniDex.c rpg.h
	$(CC) -c miniDex.c

miniInt.o: miniInt.c rpg.h
	$(CC) -c miniInt.c

miniLuk.o: miniLuk.c rpg.h
	$(CC) -c miniLuk.c

miniSTR.o: miniSTR.c rpg.h
	$(CC) -c miniSTR.c

run:
	./game

memcheck:
	valgrind --leak-check=yes ./game

clean:
	rm *.o
	rm *~
