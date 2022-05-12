CC=g++
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread
TEST_NAME=test_vector
TEST_SRC=$(TEST_NAME).cpp
PROJECT_SRC=
PROJECT_HDR=my_vector.hpp my_allocator.hpp my_iterator.hpp
PROJECT_FILES=$(PROJECT_SRC) $(PROJECT_HDR)

.PHONY: test clean

all: make_test

make_test: $(TEST_SRC) $(PROJECT_FILES)
	$(CC) $(FLAGS) $(TEST_SRC) $(PROJECT_SRC) -o $(TEST_NAME) $(TEST_LIBS)

test:
	./$(TEST_NAME)

clean:
	rm -f *.o $(TEST_NAME)
