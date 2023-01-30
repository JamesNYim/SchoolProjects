CC = gcc
CFLAGS = -std=c17  -Wall 

.PHONY: all clean debug

all: ListTest ListClient Lex

clean:
	rm -f ListTest Lex ListTest *.o

debug: CFLAGS += -g

debug: clean all 

Lex: Lex.o List.o
	$(CC) -o Lex Lex.o List.o

Lex.o: Lex.c
	$(CC) $(CFLAGS) -c Lex.c List.c

ListClient: ListClient.o List.o
	$(CC) -o ListClient ListClient.o List.o

ListClient.o: ListClient.c List.c
	$(CC) $(CFLAGS) -c ListClient.c List.c

ListTest: ListTest.o List.o
	$(CC) -o ListTest ListTest.o List.o

ListTest.o: ListTest.c List.c
	$(CC) $(CFLAGS) -c ListTest.c List.c

List.o: List.c
	$(CC) $(CFLAGS) -c List.c





