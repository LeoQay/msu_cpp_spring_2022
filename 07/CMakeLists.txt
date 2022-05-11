cmake_minimum_required(VERSION 3.16.3)
project(hw_cpp_vk)

set(CMAKE_CXX_STANDARD 20)

add_executable(07 main.cpp
        my_vector.cpp my_vector.hpp
        my_allocator.hpp
        my_iterator.hpp)

add_executable(test07 test_vector.cpp
        my_vector.cpp my_vector.hpp
        my_allocator.hpp
        my_iterator.hpp)

target_link_libraries(test07 gtest_main)
target_link_libraries(test07 gtest)
target_link_libraries(test07 pthread)
