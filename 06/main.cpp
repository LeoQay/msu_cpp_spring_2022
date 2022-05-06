#include <iostream>

#include "format.hpp"


int main()
{
    std::string f = "String {0} {2}";
    std::string s = "123";

    std::cout << format(f, s, "235", 3, 4);

    return 0;
}
