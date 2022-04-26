CC=g++
PROJECT_NAME=serializer
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread
TEST_NAME=test_$(PROJECT_NAME)
HPP_FILE=$(PROJECT_NAME).hpp

.PHONY: test clean

all: make_test

make_test:  $(HPP_FILE) $(TEST_NAME).cpp
	$(CC) $(FLAGS) $(TEST_NAME).cpp $(HPP_FILE) -o $(TEST_NAME) $(TEST_LIBS)

test:
	./$(TEST_NAME)

clean:
	rm -f *.o $(TEST_NAME)
