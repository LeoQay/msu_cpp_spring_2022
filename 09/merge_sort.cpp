#include <cstdio>
#include <iostream>
#include <algorithm>

#include "merge_sort.hpp"


size_t my_file_size(FILE * file)
{
    size_t pos = ftell(file);
    fseeko64(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseeko64(file, pos, SEEK_SET);
    return size / sizeof(int64_t);
}



MergeSort::MergeSort(int64_t * arr, size_t size) : arr_(arr), size_(size) {}


void MergeSort::sort(FILE * to_sort)
{
    std::rewind(to_sort);
    size_t size = my_file_size(to_sort);

    if (size == 0) return;
    if (size <= size_)
    {
        size_t len = std::fread(arr_, sizeof(int64_t), size_, to_sort);
        std::sort(arr_, arr_ + len);
        std::rewind(to_sort);
        std::fwrite(arr_, sizeof(int64_t), len, to_sort);
        return;
    }

    FILE * temp1 = std::tmpfile();
    FILE * temp2 = std::tmpfile();

    split(to_sort, temp1, temp2);
    sort(temp1);
    sort(temp2);
    merge(to_sort, temp1, temp2);

    std::fclose(temp1);
    std::fclose(temp2);
}


int MergeSort::split(FILE * to_split, FILE * out1, FILE * out2)
{
    std::rewind(to_split);
    std::rewind(out1);
    std::rewind(out2);

    int flag = 0;

    while (true)
    {
        size_t len = std::fread(arr_, sizeof(int64_t), size_, to_split);
        if (len == 0) break;
        std::fwrite(arr_, sizeof(int64_t), len, out1);
        ++flag;

        len = std::fread(arr_, sizeof(int64_t), size_, to_split);
        if (len == 0) break;
        std::fwrite(arr_, sizeof(int64_t), len, out2);
        ++flag;
    }

    return flag < 2 ? flag : 2;
}



void MergeSort::merge(FILE * to_merge, FILE * in1, FILE * in2)
{
    std::rewind(to_merge);
    std::rewind(in1);
    std::rewind(in2);

    size_t size = size_ / 4, pos1 = 0, pos2 = 0, len1 = 0, len2 = 0;
    size_t buf_size = size_ / 2, buf_pos = 0;
    auto arr1 = arr_, arr2 = arr_ + size, buf = arr_ + 2 * size;

    while (true)
    {
        if (buf_pos >= buf_size)
        {
            std::fwrite(buf, sizeof(int64_t), buf_pos, to_merge);
            buf_pos = 0;
        }

        if (pos1 >= len1)
        {
            len1 = std::fread(arr1, sizeof(int64_t), size, in1);
            pos1 = 0;

            if (len1 == 0)
            {
                std::swap(in1, in2);
                std::swap(arr1, arr2);
                pos1 = pos2;
                len1 = len2;
                break;
            }
        }

        if (pos2 >= len2)
        {
            len2 = std::fread(arr2, sizeof(int64_t), size, in2);
            pos2 = 0;
            if (len2 == 0) break;
        }

        if (arr1[pos1] < arr2[pos2])
        {
            buf[buf_pos++] = arr1[pos1];
            ++pos1;
        }
        else
        {
            buf[buf_pos++] = arr2[pos2];
            ++pos2;
        }
    }

    std::fwrite(buf, sizeof(int64_t), buf_pos, to_merge);
    std::fwrite(arr1 + pos1, sizeof(int64_t), len1 - pos1, to_merge);

    while (true)
    {
        len1 = std::fread(arr_, sizeof(int64_t), size_, in1);
        if (len1 == 0) break;
        std::fwrite(arr_, sizeof(int64_t), len1, to_merge);
    }
}
