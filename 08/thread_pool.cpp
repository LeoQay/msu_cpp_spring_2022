#include <thread>
#include <future>
#include <iostream>

#include "thread_pool.hpp"


ThreadPool::ThreadPool(size_t poolSize) : threads()
{
    for (size_t i = 0; i < poolSize; i++)
    {
        std::thread t(thread_function, &que);
        threads.push_back(std::move(t));
    }
}


ThreadPool::~ThreadPool()
{
    for (auto & th : threads) th.join();
}


void ThreadPool::thread_function(std::deque<SharedTask *> * ptr)
{

}

