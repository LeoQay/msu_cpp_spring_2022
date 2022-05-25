#ifndef HW_CPP_VK_THREAD_POOL_HPP
#define HW_CPP_VK_THREAD_POOL_HPP


#include <cstdlib>


class ThreadPool
{
public:
    explicit ThreadPool(size_t poolSize);

    // pass arguments by value
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;
};


#endif //HW_CPP_VK_THREAD_POOL_HPP
