#ifndef HW_CPP_VK_FOR_TESTS_HPP
#define HW_CPP_VK_FOR_TESTS_HPP

#include <thread>
#include <cmath>
#include <ctime>


int func_1841()
{
    return 1841;
}


int func_sqrt(int n)
{
    return static_cast<int>(std::sqrt(n));
}


std::string func_str_mul_int(std::string arg, int count)
{
    std::string res;
    for (int i = 0; i < count; i++) res += arg;
    return res;
}


uint64_t timed_function(uint64_t t)
{
    auto start = std::chrono::high_resolution_clock::now();

    std::this_thread::sleep_for(std::chrono::milliseconds(t));

    auto end = std::chrono::high_resolution_clock::now();

    return (end - start).count();
}





#endif //HW_CPP_VK_FOR_TESTS_HPP
