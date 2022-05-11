#include <iostream>
#include <vector>


#include "my_vector.hpp"


int main()
{
    std::vector<int, Allocator<int>> v(2000);

    for (int i = 0; i < 2000; i++) v.pop_back();



    return 0;
}
