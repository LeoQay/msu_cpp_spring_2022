#include <iostream>

#include "bigint.hpp"


using namespace std;

int main()
{
    cout << BigInt("1235454733215724378562475627") - BigInt("1235454733215724378562475626");

    return 0;
}