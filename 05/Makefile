CC=g++
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread
TEST_NAME=test_serializer

.PHONY: test clean

all: make_test

make_test: $(TEST_NAME).cpp serializer.cpp serializer.hpp deserializer.cpp deserializer.hpp
	$(CC) $(FLAGS) $(TEST_NAME).cpp serializer.cpp deserializer.cpp -o $(TEST_NAME) $(TEST_LIBS)

test:
	./$(TEST_NAME)

clean:
	rm -f *.o $(TEST_NAME)
