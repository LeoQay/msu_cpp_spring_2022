#include <string>
#include <sstream>
#include <vector>

#include "format.hpp"


Error ProcessedFormat::make(const std::string & str)
{
    clear();

    collect_scope_stat(str);
    Error err = collect_place_stat();

    if (err != Error::NoError)
    {
        clear();
        return err;
    }



    clear();
    return Error::NoError;
}


void ProcessedFormat::clear()
{
    scope_stat.clear();
    place_stat.clear();
}


void ProcessedFormat::collect_scope_stat(const std::string & str)
{
    scope_stat.clear();

    size_t pos = 0, len = str.size();

    while (pos < len)
    {
        if (str[pos] == '(')
        {
            scope_stat.emplace_back(Scope::Open, pos);
        }
        else if (str[pos] == ')')
        {
            scope_stat.emplace_back(Scope::Close, pos);
        }
        pos++;
    }
}


Error ProcessedFormat::collect_place_stat()
{
    if (scope_stat.size() % 2 != 0) return Error::FormatError;

    size_t len = scope_stat.size();

    for (size_t i = 0; i < len; i += 2)
    {
        if (!(scope_stat[i].first == Scope::Open &&
        scope_stat[i + 1].first == Scope::Close))
        {
            return Error::FormatError;
        }

        place_stat.emplace_back(scope_stat[i].second,
                                scope_stat[i + 1].second);
    }

    return Error::NoError;
}


bool ProcessedFormat::is_digit_token(const std::string & token)
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

uint64_t ProcessedFormat::convert_str_to_uint_64(const std::string & token)
{
    std::stringstream stream;
    stream << token;
    uint64_t value;
    stream >> value;
    return value;
}
