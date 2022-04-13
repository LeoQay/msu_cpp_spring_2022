cmake_minimum_required(VERSION 3.16.3)
project(hw_cpp_vk)

set(CMAKE_CXX_STANDARD 20)

add_executable(03 main.cpp matrix.cpp matrix.hpp)

add_executable(test03 test_matrix.cpp matrix.cpp matrix.hpp)

target_link_libraries(test03 gtest_main)
target_link_libraries(test03 gtest)
target_link_libraries(test03 pthread)
