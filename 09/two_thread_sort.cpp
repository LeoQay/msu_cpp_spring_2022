#include <thread>
#include <mutex>
#include <deque>
#include <cstdio>
#include <algorithm>

#include "two_thread_sort.hpp"


FILE * TwoThreadSort::sort(const std::string & file_name)
{
    phase = 1;
    first_file = fopen64(file_name.c_str(), "rb");

    for (int i = 0; i < 2; i++)
    {
        threads.emplace_back(thread_function, this);
    }

    for (int i = 0; i < 2; i++)
    {
        threads[i].join();
    }

    return temp_files_[0];
}


void TwoThreadSort::thread_function(TwoThreadSort * self)
{
    // first phase
    auto arr = new int64_t[memory_allowed];

    while (true)
    {
        size_t read_len = 0;

        {
            std::lock_guard<std::mutex> lock(self->first_file_mut);

            if (self->phase != 1) break;

            read_len = fread(arr, sizeof *arr, memory_allowed, self->first_file);

            if (read_len == 0)
            {
                self->phase = 2;
                fclose(self->first_file);
                self->first_file = nullptr;
                break;
            }
        }

        std::sort(arr, arr + read_len);
        FILE * temp = tmpfile64();
        fwrite(arr, sizeof *arr, read_len, temp);

        {
            std::lock_guard<std::mutex> lock(self->to_temp_files_);
            self->temp_files_.push_back(temp);
        }
    }

    // second phase

    size_t arr_size = memory_allowed / 4;
    size_t merged_size = memory_allowed / 2;

    auto first_arr = arr + merged_size;
    auto second_arr = first_arr + arr_size;
    auto merged_arr = arr;

    while (true)
    {
        FILE * first = nullptr;
        FILE * second = nullptr;

        {
            std::lock_guard<std::mutex> lock(self->to_temp_files_);
            if (self->temp_files_.size() <= 1) break;
            first = self->temp_files_.front();
            self->temp_files_.pop_front();
            second = self->temp_files_.front();
            self->temp_files_.pop_front();
        }

        rewind(first);
        rewind(second);

        size_t merged_ptr = 0;
        size_t cur_first_size = 1, first_ptr = 1;
        size_t cur_second_size = 1, second_ptr = 1;

        FILE * result = tmpfile64();

        while (true)
        {
            if (first_ptr >= cur_first_size)
            {
                cur_first_size = fread(first_arr, sizeof *first_arr, arr_size, first);
                first_ptr = 0;
            }

            if (second_ptr >= cur_second_size)
            {
                cur_second_size = fread(second_arr, sizeof *second_arr, arr_size, second);
                second_ptr = 0;
            }

            if (merged_ptr >= merged_size)
            {
                fwrite(merged_arr, sizeof *merged_arr, merged_ptr, result);
                merged_ptr = 0;
            }

            if (cur_first_size == 0 || cur_second_size == 0) break;

            if (first_arr[first_ptr] < second_arr[second_ptr])
            {
                merged_arr[merged_ptr++] = first_arr[first_ptr];
                ++first_ptr;
            }
            else
            {
                merged_arr[merged_ptr++] = second_arr[second_ptr];
                ++second_ptr;
            }
        }

        if (cur_second_size > 0)
        {
            fwrite(second_arr, sizeof *second_arr, cur_second_size, result);
            std::swap(first, second);
        }
        else
        {
            fwrite(first_arr, sizeof *first_arr, cur_first_size, result);
        }

        while (!feof(first))
        {
            cur_first_size = fread(merged_arr, sizeof *merged_arr, merged_size, first);
            fwrite(merged_arr, sizeof *merged_arr, cur_first_size, result);
        }

        {
            std::lock_guard<std::mutex> lock(self->to_temp_files_);
            self->temp_files_.push_back(result);
        }

        fclose(first);
        fclose(second);
    }
}
