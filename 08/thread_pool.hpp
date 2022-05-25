#ifndef HW_CPP_VK_THREAD_POOL_HPP
#define HW_CPP_VK_THREAD_POOL_HPP

#include <thread>
#include <future>
#include <functional>


class ThreadPool
{
public:
    explicit ThreadPool(size_t poolSize);

    // pass arguments by value
    template <class Func, class... ArgsT>
    auto exec(Func func, ArgsT ...args) -> std::future<decltype(func(args...))>;

private:

};


template <class Func, class... ArgsT>
auto ThreadPool::exec(Func func, ArgsT ...args) -> std::future<decltype(func(args...))>
{
    std::packaged_task<decltype(std::bind(func, args...))> task(std::bind(func, args...));

}


#endif //HW_CPP_VK_THREAD_POOL_HPP
