cmake_minimum_required(VERSION 3.16.3)
project(hw_cpp_vk)

set(CMAKE_CXX_STANDARD 20)

add_executable(05 main.cpp serializer.cpp deserializer.cpp)

add_executable(test05 test_serializer.cpp serializer.hpp deserializer.cpp)

target_link_libraries(test05 gtest_main)
target_link_libraries(test05 gtest)
target_link_libraries(test05 pthread)
