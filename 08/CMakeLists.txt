cmake_minimum_required(VERSION 3.16.3)
project(hw_cpp_vk)

set(CMAKE_CXX_STANDARD 20)

add_executable(08 main.cpp thread_pool.cpp thread_pool.hpp)

add_executable(test08 test_thread_pool.cpp thread_pool.cpp thread_pool.hpp)

target_link_libraries(test08 gtest_main)
target_link_libraries(test08 gtest)
target_link_libraries(test08 pthread)
