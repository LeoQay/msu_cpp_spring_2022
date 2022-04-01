CC=g++
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread
TEST_NAME=test_01

.PHONY: test clean

all: make_test

make_test: $(TEST_NAME).cpp allocator.o
	$(CC) $(FLAGS) $(TEST_NAME).cpp allocator.o -o $(TEST_NAME) $(TEST_LIBS)

allocator.o: allocator.cpp allocator.hpp
	$(CC) $(FLAGS) allocator.cpp -c

test:
	./$(TEST_NAME)

clean:
	rm -f *.o $(TEST_NAME)
