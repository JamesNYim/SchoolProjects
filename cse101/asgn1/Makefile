CC      = g++
CFLAGS  = -std=c++20 -Wall -Wextra -Wpedantic `pkg-config --cflags gtest`
LFLAGS  = `pkg-config --libs gtest` -lgtest_main
TARGET  = sort_test
OBJECTS = test.o

.PHONY: all tidy clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ $(LFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) $< -c

tidy:
	$(RM) $(OBJECTS)

clean: tidy
	$(RM) $(TARGET)

submit: clean
	rm -f ./asgn1.tar.gz
	tar  --exclude='*.tar.gz' -cvzf ../asgn1.tar.gz .
	mv ../asgn1.tar.gz .
