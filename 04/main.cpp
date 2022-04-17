#include <iostream>
#include <iomanip>

#include "bigint.hpp"


using namespace std;

int main()
{
    BigInt b(234), c(23);

    cout << b + c;

    return 0;
}