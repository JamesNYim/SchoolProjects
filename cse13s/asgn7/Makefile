CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g
VFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose
.PHONY: all clean format debug

all: identify

identify: identify.o node.o ht.o speck.o bv.o bf.o pq.o text.o parser.o
	$(CC) -o identify identify.o node.o ht.o speck.o bv.o bf.o pq.o text.o parser.o

identify.o: identify.c node.c ht.c speck.c bv.c bf.c pq.c text.c parser.c
	$(CC) $(CFLAGS) -c identify.c node.c ht.c speck.c bv.c bf.c pq.c text.c parser.c

parser.o : parser.c
	$(CC) $(CFLAGS) -c parser.c

text.o : text.c
	$(CC) $(CFLAGS) -c text.c

pq.o : pq.c
	$(CC) $(CFLAGS) -c pq.c

bf.o : bf.c
	$(CC) $(CFLAGS) -c bf.c

bv.o : bv.c
	$(CC) $(CFLAGS) -c bv.c

node.o : node.c 
	$(CC) $(CFLAGS) -c node.c

ht.o : ht.c speck.c 
	$(CC) $(CFLAGS) -c ht.c speck.c

speck.o : speck.c
	$(CC) $(CFLAGS) -c speck.c


format: 
	clang-format -i -style=file *.[ch]

clean :
	rm -f identify *.o

debug : all

scan-build: clean
	scan-build --use-cc=$(CC) make 
