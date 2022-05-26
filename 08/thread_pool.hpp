#ifndef HW_CPP_VK_THREAD_POOL_HPP
#define HW_CPP_VK_THREAD_POOL_HPP

#include <thread>
#include <future>
#include <functional>
#include <vector>
#include <deque>
#include <mutex>
#include <shared_mutex>
#include <iostream>


class SharedTask
{
public:
    virtual void operator() ()
    {
        std::cout << "Blin" <<std::endl;
    }
};


template<class T>
class RealTask : public SharedTask
{
public:
    explicit RealTask(T obj) : real_task(std::move(obj)) {}

    T real_task;

    void operator() () override
    {
        real_task();
    }
};


class ThreadPool
{
public:
    explicit ThreadPool(size_t poolSize);
    ~ThreadPool();

    // pass arguments by value
    template <class Func, class... ArgsT>
    auto exec(Func func, ArgsT ...args) -> std::future<decltype(func(args...))>;
private:

public:
    static void thread_function(std::deque<SharedTask *> * ptr);

    std::vector<std::thread> threads;
    std::deque<SharedTask *> que;
};


template <class Func, class... ArgsT>
auto ThreadPool::exec(Func func, ArgsT ...args) -> std::future<decltype(func(args...))>
{
    std::packaged_task<decltype(func(args...)) ()> task(std::bind(func, args...));

    auto result = task.get_future();

    auto real_task = new RealTask<decltype(task)>(std::move(task));

    que.push_back(static_cast<SharedTask *>(real_task));

    return result;
}


#endif //HW_CPP_VK_THREAD_POOL_HPP
