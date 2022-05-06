CC=g++
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread
TEST_NAME=test_format
PROJECT_SRC=format.cpp processed_format.cpp format_exception.cpp
PROJECT_HDR=format.hpp processed_format.hpp format_exception.hpp
PROJECT_DPN=$(PROJECT_SRC) $(PROJECT_HDR)

.PHONY: test clean

all: make_test

make_test: $(TEST_NAME).cpp $(PROJECT_DPN)
	$(CC) $(FLAGS) $(TEST_NAME).cpp $(PROJECT_SRC) -o $(TEST_NAME) $(TEST_LIBS)

test:
	./$(TEST_NAME)

clean:
	rm -f *.o $(TEST_NAME)
