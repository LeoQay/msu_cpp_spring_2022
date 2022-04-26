#ifndef HW_CPP_VK_DESERIALIZER_HPP
#define HW_CPP_VK_DESERIALIZER_HPP

#include <sstream>
#include <iostream>


class Deserializer
{
public:
    explicit Deserializer(std::istream & in);
private:

    std::istream & in_;
};


Deserializer::Deserializer(std::istream &in) : in_(in) {}


#endif //HW_CPP_VK_DESERIALIZER_HPP
