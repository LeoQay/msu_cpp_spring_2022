#ifndef HW_CPP_VK_SERIALIZER_HPP
#define HW_CPP_VK_SERIALIZER_HPP

#include <iostream>
#include <sstream>


enum class Error
{
    NoError,
    CorruptedArchive
};


class Serializer
{
public:
    explicit Serializer(std::ostream & out) : out_(out) {}

    template <class T>
    Error save(T & object);

    template <class... ArgsT>
    Error operator() (ArgsT... args);

    Error process(bool arg);
    Error process(uint64_t arg);

private:

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


Error Serializer::process(bool arg)
{
    try {
        out_ << separator << (arg ? "true" : "false");
    }
    catch (...)
    {
        return Error::CorruptedArchive;
    }
    return Error::NoError;
}


Error Serializer::process(uint64_t arg)
{
    try {
        out_ << separator << arg;
    }
    catch (...)
    {
        return Error::CorruptedArchive;
    }
    return Error::NoError;
}


template<class T, class... ArgsT>
Error Serializer::process(T arg, ArgsT ...args)
{
    if (process(arg) == Error::CorruptedArchive)
    {
        return Error::CorruptedArchive;
    }

    if constexpr (sizeof... (args) > 0)
    {
        if (process(args...) == Error::CorruptedArchive)
        {
            return Error::CorruptedArchive;
        }
    }

    return Error::NoError;
}



#endif //HW_CPP_VK_SERIALIZER_HPP
