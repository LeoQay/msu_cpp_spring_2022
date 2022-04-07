#include <iostream>

#include "token_parser.hpp"

int main()
{
    TokenParser obj;

    std::string s;

    getline(std::cin, s);

    obj.parse(s);

    return 0;
}