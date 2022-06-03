#include <thread>
#include <semaphore>
#include <mutex>


#include "thread_pool.hpp"


ThreadPool::ThreadPool(size_t poolSize)
: threads(), to_check(0), que(), to_que()
{
    for (size_t i = 0; i < poolSize; i++)
    {
        std::thread t(thread_function, &que, &to_check, &to_que);
        threads.push_back(std::move(t));
    }
}


ThreadPool::~ThreadPool()
{
    to_check.release(static_cast<long>(threads.size()));
    for (auto & th : threads) th.join();
    for (auto ptr : que) delete ptr;
}


void ThreadPool::thread_function(std::deque<BaseTask *> * que_,
                                 std::counting_semaphore<> * to_check_,
                                 std::mutex * to_que_)
{
    while (true)
    {
        to_check_->acquire();

        BaseTask * task;

        {
            std::lock_guard<std::mutex> guard(*to_que_);

            if (que_->empty())
            {
                return;
            }

            task = que_->front();
            que_->pop_front();
        }

        task->operator() ();
        delete task;
    }
}

