#include <iostream>

#include "two_thread_sort.hpp"


int main()
{

    TwoThreadSort sorter;
    sorter.sort("file.bin", "result.bin");

    FILE * file = fopen64("result.bin", "r");

    int64_t buffer[1024];

    while (!feof(file))
    {
        auto size = fread(buffer, sizeof *buffer, 1024, file);
        for (size_t i = 0; i < size; i++)
        {
            printf("%ld\n", buffer[i]);
        }
    }


    return 0;
}
