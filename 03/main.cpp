#include <iostream>
#include "matrix.hpp"



int main()
{
    Matrix m(5, 5);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            m[i][j] = 2;
        }
    }

    m = m * 2;

    std::cout << m;

    return 0;
}