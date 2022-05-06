#ifndef HW_CPP_VK_FORMAT_EXCEPTION_H
#define HW_CPP_VK_FORMAT_EXCEPTION_H


#include <stdexcept>


class FormatException : std::exception
{
public:
    FormatException();
    const char * what();
protected:
    std::string msg_;
};


class ScopeFormatException : public FormatException
{
public:
    explicit ScopeFormatException(size_t pos);
private:
    size_t pos_;
};


class ArgLexFormatException : public FormatException
{
public:
    explicit ArgLexFormatException(const std::string & err);
private:
    std::string err_;
};


#endif //HW_CPP_VK_FORMAT_EXCEPTION_H
