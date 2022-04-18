#include <iostream>

#include "bigint.hpp"


using namespace std;

int main()
{
    BigInt a = "2123456789";

    cout << a << std::endl;

    a -= 123456789;

    cout << a;

    return 0;
}