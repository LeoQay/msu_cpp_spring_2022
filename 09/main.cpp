#include <iostream>

#include "two_thread_sort.hpp"
#include "test_sort.hpp"


int main()
{
    Generator::gen("file.bin", 10000000);

    TwoThreadSort sorter;
    sorter.sort("file.bin", "result.bin");

    std::cout << SortChecker::check("result.bin");
    
    return 0;
}
