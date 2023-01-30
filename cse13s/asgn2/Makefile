CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic 

.PHONY: all

all: testFile integrate

integrate: integrate.o mathlib.o functions.o
	$(CC)  -o integrate integrate.o mathlib.o functions.o

testFile: testFile.o mathlib.o
	$(CC) -lm -o testFile testFile.o mathlib.o

testFile.o: testFile.c
	$(CC) $(CFLAGS)  -c testFile.c

mathlib.o: mathlib.c
	$(CC) $(CFLAGS) -c mathlib.c

integrate.o: integrate.c 
	$(CC) $(CFLAGS) -c integrate.c

functions.o: functions.c
	$(CC) $(CFLAGS) -c functions.c

clean:
	rm -f testFile.o testFile mathlib.o integrate.o integrate functions.o

format:
	clang-format -i -style=file *.[ch]



	
