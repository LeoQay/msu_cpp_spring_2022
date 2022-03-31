CC=g++
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_FLAGS=$(FLAGS) -lgtest_main -lgtest -lpthread

TEST_NAME=test_02


test: make_test run_test

make_test: $(TEST_NAME).o Allocator.o
	$(CC) $(TEST_FLAGS) $(TEST_NAME).o Allocator.o -o $(TEST_NAME)

run_test:
	./$(TEST_NAME)

$(TEST_NAME).o: $(TEST_NAME).cpp Allocator.hpp
	$(CC) $(TEST_FLAGS) $(TEST_NAME).cpp -c

Allocator.o: Allocator.cpp Allocator.hpp
	$(CC) $(TEST_FLAGS) Allocator.cpp -c

clean:
	rm -f *.o $(TEST_NAME)

