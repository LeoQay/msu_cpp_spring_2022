#include <iostream>

#include "my_shared_ptr.hpp"


int main()
{
    auto ptr = new int64_t;

    *ptr = 2;

    SharedPtr<int64_t> sh(ptr);
    SharedPtr<int64_t> emp;
    emp = sh;
    SharedPtr<int64_t> another(emp);

    (*sh)++;
    (*emp)++;
    (*another)++;

    std::cout << *emp << std::endl;

    sh.reset();
    another.reset();

    std::cout << *emp << std::endl;

    sh = another;
    another = emp;

    std::cout << *another << std::endl;
    std::cout << *emp << std::endl;

    auto again = new int64_t;
    *again = 10;

    another.reset();
    sh.reset();
    emp.reset(again);

    std::cout << *emp << std::endl;

    return 0;
}