#ifndef HW_CPP_VK_TWO_THREAD_SORT_HPP
#define HW_CPP_VK_TWO_THREAD_SORT_HPP


#include <thread>
#include <deque>
#include <mutex>
#include <cmath>



constexpr std::size_t degree(size_t val, int deg)
{
    std::size_t res = 1;
    for (int i = 0; i < deg; i++) res *= val;
    return val;
}


class TwoThreadSort
{
public:
    void sort(const std::string & inp, const std::string & out);
private:
    static void thread_function(TwoThreadSort * self);

    std::deque<std::thread> threads;



    static constexpr std::size_t memory_allowed = 7 * degree(2, 23);
};


#endif //HW_CPP_VK_TWO_THREAD_SORT_HPP
