#ifndef HW_CPP_VK_SERIALIZER_HPP
#define HW_CPP_VK_SERIALIZER_HPP

#include <iostream>
#include <sstream>

#include "error_t.h"


class Serializer
{
public:
    explicit Serializer(std::ostream & out);

    template <class T>
    Error save(T & object);

    template <class... ArgsT>
    Error operator() (ArgsT... args);

private:

    Error process(bool arg);
    Error process(uint64_t arg);

    template<class T, class... ArgsT>
    Error process(T arg, ArgsT ...args);

    std::ostream & out_;

    static constexpr char separator = ' ';
};


template <class T>
Error Serializer::save(T & object)
{
    return object.serialize(*this);
}


template <class... ArgsT>
Error Serializer::operator() (ArgsT... args)
{
    return process(args...);
}


template<class T, class... ArgsT>
Error Serializer::process(T arg, ArgsT ...args)
{
    Error ret = process(arg);

    if (ret != Error::NoError)
    {
        return ret;
    }

    if constexpr (sizeof... (args) > 0)
    {
        ret = process(args...);
        if (ret != Error::NoError)
        {
            return ret;
        }
    }

    return Error::NoError;
}



#endif //HW_CPP_VK_SERIALIZER_HPP
