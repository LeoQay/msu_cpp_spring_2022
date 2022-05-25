cmake_minimum_required(VERSION 3.16.3)
project(hw_cpp_vk)


include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)



set(CMAKE_CXX_STANDARD 20)

add_executable(08 main.cpp thread_pool.cpp thread_pool.hpp)

add_executable(test08 test_thread_pool.cpp thread_pool.cpp thread_pool.hpp)

target_link_libraries(test08 gtest_main)
target_link_libraries(test08 gtest)
target_link_libraries(test08 pthread)
