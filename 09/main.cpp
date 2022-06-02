#include <iostream>

#include "two_thread_sort.hpp"


int main()
{

    TwoThreadSort sorter;
    sorter.sort("file.bin", "result.bin");

    FILE * file = fopen("result.bin", "rb");

    int64_t buffer[10000];

    size_t pos = 0;

    while (!feof(file))
    {
        auto size = fread(buffer, sizeof *buffer, 10000, file);
        for (size_t i = 0; i < size; i++)
        {
            pos++;
            //printf("%ld\n", buffer[i]);
            if (i < size - 2 && buffer[i] > buffer[i + 1]) printf("Blin %ld\n", pos);
        }
    }


    return 0;
}
