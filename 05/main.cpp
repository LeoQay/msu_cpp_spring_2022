#include <iostream>

#include "serializer.hpp"



struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer & serializer)
    {
        return serializer(a, b, c);
    }
};




int main()
{
    Data x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data y { 0, false, 0 };

    serializer.save(y);

    std::string str = stream.str();


    return 0;
}
