#include <string>
#include <algorithm>

#include "token_parser.hpp"


void TokenParser::do_start_call()
{
    do_call(start_call);
}

void TokenParser::do_end_call()
{
    do_call(end_call);
}

void TokenParser::do_digit_call(const std::string & token)
{
    do_call(digit_call, token);
}

void TokenParser::do_token_call(const std::string & token)
{
    do_call(token_call, token);
}

void TokenParser::do_string_call(const std::string & token)
{
    do_call(string_call, token);
}


void TokenParser::set_end_call(call_f callback)
{
    this->end_call = callback;
}

void TokenParser::set_start_call(call_f callback)
{
    this->start_call = callback;
}

void TokenParser::set_digit_call(call_str_f callback)
{
    this->digit_call = callback;
}

void TokenParser::set_string_call(call_str_f callback)
{
    this->string_call = callback;
}

void TokenParser::set_token_call(call_str_f callback)
{
    this->token_call = callback;
}


void TokenParser::parse(const std::string & line)
{
    do_start_call();

    token_stack.clear();

    split(line);

    for (auto & token : token_stack)
    {
        do_call(token_call, token);

        if (is_digit_token(token))
        {
            do_digit_call(token);
        }
        else
        {
            do_string_call(token);
        }
    }

    do_end_call();
}


void TokenParser::do_call(call_f callback)
{
    if (!callback)
    {
        return;
    }

    callback();
}

void TokenParser::do_call(call_str_f callback, const std::string & token)
{
    if (!callback)
    {
        return;
    }

    callback(token);
}


void TokenParser::split(const std::string & line)
{
    size_t pos = 0;
    size_t len = line.size();

    while (true)
    {
        while (pos < len && isspace(line[pos]))
        {
            pos++;
        }

        if (pos >= len)
        {
            return;
        }

        size_t start = pos;

        while (pos < len && !isspace(line[pos]))
        {
            pos++;
        }

        token_stack.push_back(line.substr(start, pos - start));
    }
}

bool TokenParser::is_digit_token(const std::string & token)
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
