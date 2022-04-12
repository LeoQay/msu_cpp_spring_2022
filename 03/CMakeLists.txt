cmake_minimum_required(VERSION 3.16.3)
project(hw_cpp_vk)

set(CMAKE_CXX_STANDARD 20)

add_executable(03 main.cpp matrix.cpp test_matrix.cpp)

target_link_libraries(03 gtest_main)
target_link_libraries(03 gtest)
target_link_libraries(03 gmock)
target_link_libraries(03 pthread)
