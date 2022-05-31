#include <iostream>

#include "two_thread_sort.hpp"


int main()
{

    TwoThreadSort sorter;
    FILE * file = sorter.sort("file.bin");

    rewind(file);


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
