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

private:

    Error process(bool & value);

    Error process(uint64_t & value);
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


Error Deserializer::process(bool & value)
{
    std::string text;
    in_ >> text;

    if (in_.fail())
    {
        return Error::ReadError;
    }

    if (text == "true")
    {
        value = true;
    }
    else if (text == "false")
    {
        value = false;
    }
    else
    {
        return Error::CorruptedArchive;
    }

    return Error::NoError;
}


Error Deserializer::process(uint64_t & value)
{
    std::string str;
    in_ >> str;

    if (in_.fail())
    {
        return Error::ReadError;
    }

    if (is_digit_token(str))
    {
        value = convert_str_to_uint_64(str);
    }
    else
    {
        return Error::CorruptedArchive;
    }

    return Error::NoError;
}


bool Deserializer::is_digit_token(const std::string & token)
{
    if (!std::all_of(token.begin(), token.end(),
                     [] (char sym) { return isdigit(sym); } ))
    {
        return false;
    }

    size_t start = 0, len = token.size();
    while (start < len && token[start] == '0')
    {
        start++;
    }

    std::string num = token.substr(start);

    if (num.empty())
    {
        return true;
    }

    // for uint64_t from <stdint.h>
    std::string max_value = "18446744073709551615";

    if (num.size() > max_value.size())
    {
        return false;
    }
    else if (num.size() < max_value.size())
    {
        return true;
    }

    // length is equal
    return num <= max_value;
}

uint64_t Deserializer::convert_str_to_uint_64(const std::string & token)
{
    std::stringstream stream;
    stream << token;
    uint64_t value;
    stream >> value;
    return value;
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
