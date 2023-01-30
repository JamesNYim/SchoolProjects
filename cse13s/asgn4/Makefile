CC = clang
CFLAGS  = -Wall -Wextra -Wpedantic `pkg-config --cflags ncurses`
LFLAGS  = $(shell pkg-config --libs ncurses)

.PHONY: all clean format

all: life

life: life.o universe.o 
	$(CC) -o life life.o universe.o -lncurses

life.o: life.c
	$(CC) $(CFLAGS) -c life.c

universe.o: universe.c
	$(CC) $(CFLAGS) -c universe.c

clean:
	rm -f life life.o universe.o

format:
	clang-format -i -style=file *.[ch]
