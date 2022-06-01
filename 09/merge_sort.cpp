#include <cstdio>

#include "merge_sort.hpp"


template<typename intT>
MergeSort<intT>::MergeSort(intT * arr, size_t size) : arr_(arr), size_(size) {}


template<typename intT>
void MergeSort<intT>::sort(FILE * to_sort)
{
    std::rewind(to_sort);

    size_t size = fseeko64(to_sort, 0, SEEK_END);
    if (size == 0) return;
    if (size <= size_)
    {
        size_t len = std::fread(arr_, sizeof(intT), size_, to_sort);
        std::sort(arr_, arr_ + len);
        fseeko64(to_sort, 0, SEEK_SET);
        std::fwrite(arr_, sizeof(intT), len, to_sort);
        return;
    }

    FILE * temp1 = std::tmpfile();
    FILE * temp2 = std::tmpfile();

    split(to_sort, temp1, temp2);

    sort(temp1);
    sort(temp2);

    fseeko64(to_sort, 0, SEEK_SET);
    merge(to_sort, temp1, temp2);

    std::fclose(temp1);
    std::fclose(temp2);
}


template<typename intT>
int MergeSort<intT>::split(FILE * to_split, FILE * out1, FILE * out2)
{
    // update feof
    std::fread(arr_, sizeof(intT), 0, to_split);

    int flag = 0;

    while (true)
    {
        if (std::feof(to_split)) break;
        size_t len = std::fread(arr_, sizeof(intT), size_, to_split);
        std::fwrite(arr_, sizeof(intT), len, out1);
        ++flag;

        if (std::feof(to_split)) break;
        len = std::fread(arr_, sizeof(intT), size_, to_split);
        std::fwrite(arr_, sizeof(intT), len, out2);
        ++flag;
    }

    return flag < 2 ? flag : 2;
}


template<typename intT>
void MergeSort<intT>::merge(FILE * to_merge, FILE * in1, FILE * in2)
{
    size_t size = size_ / 4, pos1 = 0, pos2 = 0, len1, len2;
    size_t buf_size = size / 2, buf_pos = 0;
    auto arr1 = arr_, arr2 = arr_ + size, buf = arr_ + 2 * size;

    // update feof
    std::fread(arr_, sizeof(intT), 0, in1);
    std::fread(arr_, sizeof(intT), 0, in2);

    while (true)
    {
        if (buf_pos >= buf_size)
        {
            std::fwrite(buf, sizeof(intT), buf_size, to_merge);
            buf_pos = 0;
        }

        if (pos1 >= len1)
        {
            if (std::feof(in1))
            {
                std::swap(in1, in2);
                std::swap(arr1, arr2);
                pos1 = pos2;
                len1 = len2;
                break;
            }
            len1 = std::fread(arr1, sizeof(intT), size, in1);
            pos1 = 0;
        }

        if (pos2 >= len2)
        {
            if (std::feof(in2)) break;
            len2 = std::fread(arr2, sizeof(intT), size, in2);
            pos2 = 0;
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

    std::fwrite(buf, sizeof(intT), buf_pos, to_merge);
    std::fwrite(arr1, sizeof(intT), pos1, to_merge);

    while (!std::feof(in1))
    {
        len1 = std::fread(arr_, sizeof(intT), size_, in1);
        std::fwrite(arr_, sizeof(intT), len1, to_merge);
    }
}
