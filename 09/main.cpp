#include <iostream>

#include "two_thread_sort.hpp"


int main()
{
/*
    TwoThreadSort sorter;
    sorter.sort("file.bin", "result.bin");
*/
    FILE * file = fopen("result.bin", "rb");

    int64_t buffer[10000];

    while (!feof(file))
    {
        auto size = fread(buffer, sizeof *buffer, 10000, file);
        for (size_t i = 0; i < size - 1; i++)
        {
            if (buffer[i] > buffer[i + 1]) printf("Blin\n");
        }
    }


    return 0;
}
