cmake_minimum_required(VERSION 3.16.3)
project(hw_cpp_vk)

set(CMAKE_CXX_STANDARD 20)

add_executable(09 main.cpp
        two_thread_sort.hpp two_thread_sort.cpp
        merge_sort.cpp merge_sort.hpp test_sort.hpp)

add_executable(test09 test_sort.cpp test_sort.hpp
        two_thread_sort.hpp two_thread_sort.cpp
        merge_sort.cpp merge_sort.hpp test_sort.hpp)

target_link_libraries(test09 gtest_main)
target_link_libraries(test09 gtest)
target_link_libraries(test09 pthread)
