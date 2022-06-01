#ifndef HW_CPP_VK_MERGE_SORT_HPP
#define HW_CPP_VK_MERGE_SORT_HPP

#include <algorithm>
#include <cstdio>


using intT = int64_t;


class MergeSort
{
public:
    MergeSort(intT * arr, size_t size);
    int split(FILE * to_split, FILE * out1, FILE * out2);
    void merge(FILE * out, FILE * in1, FILE * in2);
    void sort(FILE * to_sort);
private:
    intT * arr_;
    size_t size_;
};


#endif //HW_CPP_VK_MERGE_SORT_HPP
