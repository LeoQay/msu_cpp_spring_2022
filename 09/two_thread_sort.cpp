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
    std::filesystem::remove(out);
    std::filesystem::copy_file(inp, out);

    if (!arr_) arr_ = new int64_t[memory_allowed];

    FILE * out_file = fopen64(out.c_str(), "rb+");

    FILE * temp1 = std::tmpfile();
    FILE * temp2 = std::tmpfile();
    MergeSort sorter(arr_, memory_allowed);
    sorter.split(out_file, temp1, temp2);

    threads.emplace_back(thread_function, temp1, arr_);
    threads.emplace_back(thread_function, temp2, arr_ + memory_allowed / 2);

    for (int i = 0; i < 2; i++)
    {
        threads[i].join();
    }

    sorter.merge(out_file, temp1, temp2);

    std::fclose(temp1);
    std::fclose(temp2);
    std::fclose(out_file);
}


void TwoThreadSort::thread_function(FILE * file, int64_t * arr)
{
    MergeSort sorter(arr, memory_allowed / 2);

    sorter.sort(file);
}
