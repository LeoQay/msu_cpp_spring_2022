#include <iostream>

#include "my_vector.hpp"


int main()
{
    int * arr = new int[20];

    auto it = VectorIterator<int>(arr);
    auto it2 = it + 12;

    return 0;
}
