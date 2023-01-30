CC = gcc
CFLAGS = -std=c17 -Wall
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

EXECS = FindPath GraphTest

.PHONY: poop all clean debug

all: $(EXECS)

clean:
	rm -f $(OBJ) $(EXECS)

debug:	$(CFLAGS) += -g

debug: clean all

$(EXECS): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXECS) 

%.o: %.c
	$(CC) $(CFLAGS) -c $<

poop: 
	echo $(OBJ)
