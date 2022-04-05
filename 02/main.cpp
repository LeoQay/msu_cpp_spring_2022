#include <iostream>

#include "token_parser.hpp"

int main()
{
    TokenParser obj;

    std::string s;

    getline(std::cin, s);

    obj.Parse(s);

    return 0;
}