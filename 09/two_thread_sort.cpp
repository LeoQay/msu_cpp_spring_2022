#include <thread>
#include <mutex>
#include <deque>
#include <cstdio>
#include <algorithm>

#include "two_thread_sort.hpp"


void TwoThreadSort::sort(const std::string & file_name)
{
    phase = 1;
    first_file = fopen64(file_name.c_str(), "r");

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
    // first phase
    auto arr = new int64_t[memory_allowed];

    while (self->phase == 1)
    {
        size_t read_len = 0;
        {
            std::lock_guard<std::mutex> lock(self->first_file_mut);
            read_len = fread(arr, sizeof *arr, memory_allowed, self->first_file);
        }
        if (read_len == 0)
        {
            self->phase = 2;
            break;
        }

        std::sort(arr, arr + read_len);
        FILE * temp = tmpfile64();
        fwrite(arr, sizeof *arr, read_len, temp);

        {
            std::lock_guard<std::mutex> lock(self->to_temp_files_[0]);
            self->temp_files_[0].push_back(temp);
        }
    }

    // second phase


}

