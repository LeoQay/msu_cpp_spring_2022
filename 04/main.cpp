#include <iostream>

#include "bigint.hpp"


using namespace std;

int main()
{
    BigInt a("9999");

    cout << a + a;

    return 0;
}