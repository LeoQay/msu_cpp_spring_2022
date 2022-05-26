#include <iostream>
#include <cmath>

#include "thread_pool.hpp"


int f(int x, int y)
{

    return std::pow(x, y);
}


int main()
{

    std::cout << std::thread::hardware_concurrency() << std::endl;

    ThreadPool pool(4);


    for (int i = 0; i < 1000; i++)
    {
        pool.exec(f, 2, 12);
    }

    auto fut = pool.exec(f, 2, 12);

    for (int i = 0; i < 1000; i++)
    {
        pool.exec(f, 2, 12);
    }

    int sm = fut.get();




    std::cout << sm << std::endl;


    return 0;
}