CC=g++
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread
TEST_NAME=test_matrix

.PHONY: test clean

all: make_test

make_test: $(TEST_NAME).cpp matrix.o
	$(CC) $(FLAGS) $(TEST_NAME).cpp matrix.o -o $(TEST_NAME) $(TEST_LIBS)

matrix.o: matrix.cpp matrix.hpp
	$(CC) $(FLAGS) matrix.cpp -c

test:
	./$(TEST_NAME)

clean:
	rm -f *.o $(TEST_NAME)
