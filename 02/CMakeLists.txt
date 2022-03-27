cmake_minimum_required(VERSION 3.16.3)
project(02)

set(CMAKE_CXX_STANDARD 20)

add_executable(02 test_02.cpp Allocator.cpp Allocator.h)
