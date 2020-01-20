ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: game.o funcs.o combat.o miniDex.o miniInt.o miniLuk.o miniStr.o
	$(CC) -o game game.o funcs.o miniDex.o miniInt.o miniLuk.o miniStr.o -lm
	$(CC) -o combat combat.o funcs.o -lm

game.o: game.c rpg.h
	gcc rpg.h
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

miniStr.o: miniStr.c rpg.h
	$(CC) -c miniStr.c

run:
	./game

memcheck:
	valgrind --leak-check=yes ./game

clean:
	rm *.o
	rm *~
