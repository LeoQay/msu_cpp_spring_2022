CC=g++
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread
TEST_NAME=test_01

.PHONY: test clean

all: make_test

make_test: $(TEST_NAME).cpp Allocator.o
	$(CC) $(FLAGS) $(TEST_NAME).cpp Allocator.o -o $(TEST_NAME) $(TEST_LIBS)

Allocator.o: Allocator.cpp Allocator.hpp
	$(CC) $(FLAGS) Allocator.cpp -c

test:
	./$(TEST_NAME)

clean:
	rm -f *.o $(TEST_NAME)
