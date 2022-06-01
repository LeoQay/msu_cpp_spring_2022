#include <cstdio>

#include "merge_sort.h"


template<typename intT>
MergeSort<intT>::MergeSort() : arr_(nullptr), size_(0) {}


template<typename intT>
void MergeSort<intT>::set_buffer(intT * arr, size_t size)
{
    arr_ = arr;
    size_ = size;
}


template<typename intT>
int MergeSort<intT>::split(FILE * to_split, FILE * out1, FILE * out2)
{
    std::rewind(to_split);
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
