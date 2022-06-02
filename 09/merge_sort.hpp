#ifndef HW_CPP_VK_MERGE_SORT_HPP
#define HW_CPP_VK_MERGE_SORT_HPP

#include <cstdio>


class MergeSort
{
public:
    MergeSort(int64_t * arr, size_t size);
    int split(FILE * to_split, FILE * out1, FILE * out2);
    void merge(FILE * out, FILE * in1, FILE * in2);
    void sort(FILE * to_sort);
private:
    int64_t * arr_;
    size_t size_;
};


#endif //HW_CPP_VK_MERGE_SORT_HPP
