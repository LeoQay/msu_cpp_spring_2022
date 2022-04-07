CC=g++
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread
TEST_NAME=test_token_parser

.PHONY: test clean

all: make_test

make_test: $(TEST_NAME).cpp token_parser.o
	$(CC) $(FLAGS) $(TEST_NAME).cpp token_parser.o -o $(TEST_NAME) $(TEST_LIBS)

token_parser.o: token_parser.cpp token_parser.hpp
	$(CC) $(FLAGS) token_parser.cpp -c

test:
	./$(TEST_NAME)

clean:
	rm -f *.o $(TEST_NAME)

