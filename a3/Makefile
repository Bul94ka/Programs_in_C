CFLAGS=-std=c99 -Wall -g

all: game

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm *.o
	rm game

game: main.o game.o world.o
	gcc main.o game.o world.o -lcurses -lm -o game

