cmake_minimum_required(VERSION 3.16.3)
project(hw_cpp_vk)

set(CMAKE_CXX_STANDARD 20)

add_executable(06 main.cpp format.cpp format.hpp
        processed_format.cpp processed_format.hpp
        format_exception.cpp format_exception.hpp)

add_executable(test06 test_format.cpp format.cpp format.hpp
        processed_format.cpp processed_format.hpp
        format_exception.cpp format_exception.hpp)

target_link_libraries(test06 gtest_main)
target_link_libraries(test06 gtest)
target_link_libraries(test06 pthread)
