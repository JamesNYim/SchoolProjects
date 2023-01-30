CC      = g++
CFLAGS  = -std=c++20 -Wall -Wextra -Wpedantic -fdiagnostics-color=always
LFLAGS  =
TARGETS = generator
MODULES = grid util
OBJECTS = $(patsubst %,%.o,$(MODULES))
TOBJECTS= $(patsubst %,%.o,$(TARGETS))      # target objects

.PHONY: all debug clean tidy test

all: CFLAGS += -O3 -s
all: $(TARGETS)

debug: CFLAGS += -g
debug: $(TARGETS)

$(TARGETS): %: %.o $(OBJECTS)
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.cpp %.h
	$(CC) -c $< $(CFLAGS)

$(TOBJECTS): %.o: %.cpp
	$(CC) -c $< $(CFLAGS)

test: all
	@ ./.scripts/testgen.sh

clean: tidy
	$(RM) $(TARGETS)
	$(RM) asgn2.tar.gz

tidy:
	$(RM) $(OBJECTS) $(patsubst %,%.o,$(TARGETS))

submit: clean
	tar --exclude='*.tar.gz' --exclude=examples --exclude=.git --exclude=.gitignore \
		-cvzf asgn2.tar.gz .
