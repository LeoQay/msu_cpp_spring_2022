cmake_minimum_required(VERSION 3.16.3)
project(01)

set(CMAKE_CXX_STANDARD 20)

add_executable(02 test_token_parser.cpp token_parser.cpp token_parser.hpp)

target_link_libraries(02 gtest_main)
target_link_libraries(02 gtest)
target_link_libraries(02 gmock)
target_link_libraries(02 pthread)

