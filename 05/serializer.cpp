#include "serializer.hpp"


Serializer::Serializer(std::ostream & out) : out_(out) {}


Error Serializer::process(bool arg)
{
    try {
        out_ << separator << (arg ? "true" : "false");
    }
    catch (...)
    {
        return Error::WriteError;
    }

    return out_.fail() ? Error::WriteError : Error::NoError;
}


Error Serializer::process(uint64_t arg)
{
    try {
        out_ << separator << arg;
    }
    catch (...)
    {
        return Error::WriteError;
    }

    return out_.fail() ? Error::WriteError : Error::NoError;
}
