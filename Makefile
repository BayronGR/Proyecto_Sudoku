CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`

all: sudoku

sudoku: interface.o game_logic.o
	$(CC) -o sudoku interface.o game_logic.o $(LIBS)

interface.o: interface.c game_logic.h
	$(CC) -c interface.c $(CFLAGS)

game_logic.o: game_logic.c game_logic.h
	$(CC) -c game_logic.c $(CFLAGS)

clean:
	rm -f *.o sudoku
