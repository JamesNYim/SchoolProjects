CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g 


.PHONY: all clean format debug

all: test decode encode

test: test.o node.o pq.o stack.o code.o io.o huffman.o
	$(CC) -o test test.o node.o pq.o stack.o code.o io.o huffman.o

test.o : test.c node.c pq.c stack.c code.c io.c huffman.c
	$(CC) $(CFLAGS) -c test.c node.c pq.c stack.c code.c io.c huffman.c

decode: decode.o node.o pq.o stack.o code.o io.o huffman.o
	$(CC) -o decode decode.o node.o pq.o stack.o code.o io.o huffman.o

decode.o : decode.c node.c pq.c stack.c code.c io.c huffman.c
	$(CC) $(CFLAGS) -c decode.c node.c pq.c stack.c code.c io.c huffman.c

encode: encode.o node.o pq.o stack.o code.o io.o huffman.o
	$(CC) -o encode encode.o node.o pq.o stack.o code.o io.o huffman.o

encode.o : encode.c node.c pq.c stack.c code.c io.c huffman.c
	$(CC) $(CFLAGS) -c encode.c node.c pq.c stack.c code.c io.c huffman.c

huffman.o: huffman.c
	$(CC) $(CFLAGS) -c huffman.c

io.o: io.c
	$(CC) $(CFLAGS) -c io.c

code.o: code.c
	$(CC) $(CFLAGS) -c code.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

nodes.o: node.c
	$(CC) $(CFLAGS) -c nodes.c

pq.o: pq.c
	$(CC) $(CFLAGS) -c pq.c

format:
	clang-format -i -style=file *.[ch]

clean:
	rm -f test decode encode *.o

debug: all

scan-build: clean
	scan-build --use-cc=$(CC) make
