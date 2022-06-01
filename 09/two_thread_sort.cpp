#include <thread>
#include <mutex>
#include <deque>
#include <cstdio>
#include <algorithm>

#include "two_thread_sort.hpp"
#include "merge_sort.hpp"


TwoThreadSort::~TwoThreadSort()
{
    delete [] arr_;
}


void TwoThreadSort::sort(const std::string & inp, const std::string & out)
{
    FILE * inp_file = fopen64(inp.c_str(), "rb");



    for (int i = 0; i < 2; i++)
    {
        threads.emplace_back(thread_function, this);
    }

    for (int i = 0; i < 2; i++)
    {
        threads[i].join();
    }
}


void TwoThreadSort::thread_function(TwoThreadSort * self)
{

}
