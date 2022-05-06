#include <string>
#include <sstream>
#include <vector>

#include "processed_format.hpp"
#include "format_exception.hpp"


void ProcessedFormat::make(const std::string & str)
{
    try {
        clear_target();
        collect_scope_stat(str);
        collect_place_stat();
        build_target(str);
    }
    catch (...)
    {
        clear_target();
        clear_service();
        throw;
    }

    clear_service();
}


void ProcessedFormat::build_target(const std::string & str)
{
    if (place_stat.empty())
    {
        substrings.push_back(str);
        return;
    }

    size_t prev_end = 0, place_len = place_stat.size();

    for (size_t i = 0; i != place_len; i++)
    {
        auto [l, r] = place_stat[i];

        substrings.push_back(str.substr(prev_end, l - prev_end));

        auto arg_str = str.substr(l + 1, r - l - 1);
        strip(arg_str);

        if (!is_digit_token(arg_str))
        {
            throw ArgLexFormatException(arg_str);
        }

        arg_num.push_back(str_to_uint(arg_str));

        prev_end = r + 1;
    }

    substrings.push_back(str.substr(prev_end));
}


void ProcessedFormat::clear_service()
{
    scope_stat.clear();
    place_stat.clear();
}


void ProcessedFormat::clear_target()
{
    substrings.clear();
    arg_num.clear();
}


void ProcessedFormat::collect_scope_stat(const std::string & str)
{
    scope_stat.clear();

    size_t pos = 0, len = str.size();

    while (pos < len)
    {
        if (str[pos] == '{')
        {
            scope_stat.emplace_back(Scope::Open, pos);
        }
        else if (str[pos] == '}')
        {
            scope_stat.emplace_back(Scope::Close, pos);
        }
        pos++;
    }
}


void ProcessedFormat::collect_place_stat()
{
    if (scope_stat.size() % 2 != 0)
    {
        throw ScopeFormatException(scope_stat.back().second + 1);
    }

    size_t len = scope_stat.size();

    for (size_t i = 0; i < len; i += 2)
    {
        bool cond_l = scope_stat[i].first == Scope::Open;
        bool cond_r = scope_stat[i + 1].first == Scope::Close;
        if (!(cond_l && cond_r))
        {
            throw ScopeFormatException(
            !cond_l ? scope_stat[i].second : scope_stat[i + 1].second
            );
        }

        place_stat.emplace_back(scope_stat[i].second,
                                scope_stat[i + 1].second);
    }
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

uint64_t ProcessedFormat::str_to_uint(const std::string & token)
{
    std::stringstream stream;
    stream << token;
    uint64_t value;
    stream >> value;
    return value;
}


std::string & ProcessedFormat::strip(std::string & str)
{
    size_t pos = 0, len = str.size();
    while (pos < len && std::isspace(str[pos])) pos++;
    str.erase(0, pos);

    if (str.empty()) return str;

    pos = str.size() - 1;
    while (pos != 0 && std::isspace(str[pos])) pos--;
    str.erase(pos + 1);
    if (str.size() == 1 && std::isspace(str[0])) str.erase(0, 1);

    return str;
}
