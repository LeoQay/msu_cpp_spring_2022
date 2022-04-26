#ifndef HW_CPP_VK_DESERIALIZER_H
#define HW_CPP_VK_DESERIALIZER_H


#include <iostream>
#include <sstream>

#include "error_t.h"



class Deserializer
{
public:
    explicit Deserializer(std::istream & in);

    template<class T>
    Error load(T & object);

    template<class... ArgsT>
    Error operator() (ArgsT & ...args);

    Error process(bool & value);
    Error process(uint64_t & value);

private:

    static bool is_digit_token(const std::string & token);
    static uint64_t convert_str_to_uint_64(const std::string & token);

    template<class T, class... ArgsT>
    Error process(T & arg, ArgsT & ...args);

    std::istream & in_;
};


template<class T>
Error Deserializer::load(T & object)
{
    return object.deserialize(*this);
}


template<class... ArgsT>
Error Deserializer::operator() (ArgsT & ...args)
{
    return process(args...);
}


template<class T, class... ArgsT>
Error Deserializer::process(T & arg, ArgsT & ...args)
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



#endif //HW_CPP_VK_DESERIALIZER_H
