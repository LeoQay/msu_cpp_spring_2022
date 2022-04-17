#include <iostream>

#include "bigint.hpp"


using namespace std;

int main()
{
    BigInt a = -123;
    BigInt b = 123;

    a += b;

    cout << a;

    return 0;
}