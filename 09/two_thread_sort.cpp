#include <thread>
#include <filesystem>
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
    std::filesystem::copy_file(inp, out);

    if (!arr_) arr_ = new int64_t[memory_allowed];

    FILE * out_file = fopen64(out.c_str(), "rb+");

    MergeSort sorter(arr_, memory_allowed);
    sorter.sort(out_file);

    fclose(out_file);
    return;

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
