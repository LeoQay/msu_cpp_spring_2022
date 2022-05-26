#include <iostream>
#include <thread>
#include <future>
#include <functional>
#include <cmath>
#include <deque>

#include "thread_pool.hpp"

int f(int x, int y)
{

    return std::pow(x, y);
}



int main()
{

    std::cout << std::thread::hardware_concurrency() << std::endl;

    ThreadPool pool(1);

    auto fut = pool.exec(f, 2, 12);

    int sm = fut.get();


    std::cout << sm << std::endl;


    return 0;
}