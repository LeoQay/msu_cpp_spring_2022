#include "token_parser.hpp"

void TokenParser::SetDigitCallback(call_f callback)
{
    this->digit_call = callback;
}

void TokenParser::SetEndCallback(call_f callback)
{
    this->end_call = callback;
}

void TokenParser::SetStartCallback(call_f callback)
{
    this->start_call = callback;
}

void TokenParser::SetStringCallback(call_f callback)
{
    this->string_call = callback;
}

void TokenParser::SetTokenCallback(call_f callback)
{
    this->token_call = callback;
}
