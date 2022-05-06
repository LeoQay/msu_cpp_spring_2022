#include "format_exception.hpp"

#include <stdexcept>
#include <sstream>


FormatException::FormatException()
: std::exception(), msg_("Format Exception") {}


const char * FormatException::what()
{
    return msg_.c_str();
}


ScopeFormatException::ScopeFormatException(size_t pos)
: FormatException() , pos_(pos)
{
    std::stringstream stream;
    stream << pos_;
    msg_ = "Scope error in position: " + stream.str();
}


ArgLexFormatException::ArgLexFormatException(const std::string & err)
: err_(err)
{
    msg_ = "Lex error of argument in: " + err;
}

