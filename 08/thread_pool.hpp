#ifndef HW_CPP_VK_THREAD_POOL_HPP
#define HW_CPP_VK_THREAD_POOL_HPP

#include <thread>
#include <future>
#include <functional>
#include <vector>
#include <deque>
#include <mutex>
#include <semaphore>


class SharedTask
{
public:
    virtual void operator() () = 0;
    virtual ~SharedTask() = default;
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
    static void thread_function(std::deque<SharedTask *> * que_,
                                std::counting_semaphore<> * to_check_,
                                std::mutex * to_que_);

    std::vector<std::thread> threads;
    std::counting_semaphore<> to_check;

    std::deque<SharedTask *> que;
    std::mutex to_que;
};


template <class Func, class... ArgsT>
auto ThreadPool::exec(Func func, ArgsT ...args) -> std::future<decltype(func(args...))>
{
    std::packaged_task<decltype(func(args...)) ()> task(std::bind(func, args...));

    auto result = task.get_future();

    auto real_task = new RealTask<decltype(task)>(std::move(task));

    que.push_back(static_cast<SharedTask *>(real_task));

    to_check.release();

    return result;
}


#endif //HW_CPP_VK_THREAD_POOL_HPP
