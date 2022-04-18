#include <iostream>

#include "bigint.hpp"


using namespace std;

int main()
{
    BigInt a("35575674867347647856746546534");
    BigInt b("88734563475673463478534765746");

    a *= b;

    cout << a;

    return 0;
}