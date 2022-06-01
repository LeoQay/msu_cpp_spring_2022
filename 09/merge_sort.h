#ifndef HW_CPP_VK_MERGE_SORT_H
#define HW_CPP_VK_MERGE_SORT_H


#include <cstdio>


template<typename intT>
class MergeSort
{
public:
    MergeSort();
    void set_buffer(intT * arr, size_t size);

    int split(FILE * to_split, FILE * out1, FILE * out2);

private:
    intT * arr_;
    size_t size_;
};


#endif //HW_CPP_VK_MERGE_SORT_H
