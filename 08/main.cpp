#include <iostream>
#include <thread>
#include <future>
#include <functional>
#include <cmath>
#include <deque>

#include "thread_pool.hpp"

int f(int x, int y)
{
    std::cout << "HAHA";
    return std::pow(x, y);
}


typedef void (*p_func) ();


int main()
{

    std::cout << std::thread::hardware_concurrency() << std::endl;

    ThreadPool pool(1);

    pool.exec(f, 1, 2);

    return 0;
}