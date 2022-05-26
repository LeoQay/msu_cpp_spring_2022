#ifndef HW_CPP_VK_FORMAT_H
#define HW_CPP_VK_FORMAT_H


#include <string>
#include <vector>
#include <algorithm>

#include "processed_format.hpp"
#include "format_exception.hpp"


template<typename T, class... ArgsT>
void collect(
        std::vector<std::string> & cont,
        const T & obj,
        const ArgsT & ...args)
{
    std::stringstream stream;
    stream << obj;
    cont.push_back(stream.str());

    if constexpr (sizeof...(args) > 0)
    {
        collect(cont, args...);
    }
}


template<class... ArgsT>
std::string format(const std::string & str, const ArgsT & ...args)
{
    ProcessedFormat proc;
    proc.make(str);

    if (proc.arg_num.empty())
    {
        return str;
    }

    auto val = *std::max_element(proc.arg_num.begin(), proc.arg_num.end());

    if (val + 1 > sizeof...(args))
    {
        throw ArgsAmountFormatException(val + 1, sizeof...(args));
    }

    std::vector<std::string> arguments;

    if constexpr (sizeof...(args) > 0)
    {
        collect(arguments, args...);
    }
    else
    {
        // never reached
        throw ArgsAmountFormatException(val + 1, 0);
    }

    std::string result = proc.substrings[0];
    size_t len = proc.arg_num.size();

    for (size_t i = 0; i != len; i++)
    {
        result += arguments[proc.arg_num[i]];
        result += proc.substrings[i + 1];
    }

    return result;
}


#endif //HW_CPP_VK_FORMAT_H
