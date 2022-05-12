#include <iostream>
#include <vector>


#include "my_vector.hpp"


class A
{
public:
    A() {std::cout << "A::A()\n";}
    ~A() {std::cout << "A::~A()\n";}
};


int main()
{
    std::vector<A, Allocator<A>> v(4);

    v.resize(2);


    return 0;
}
