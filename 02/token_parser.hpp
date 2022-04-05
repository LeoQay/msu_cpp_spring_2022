#ifndef INC_01_TOKEN_PARSER_H
#define INC_01_TOKEN_PARSER_H

#include <string>

typedef void (*call_f) (std::string &);

class TokenParser
{
public:
    TokenParser() = default;

    void SetStartCallback(call_f callback);

    void SetEndCallback(call_f callback);

    void SetTokenCallback(call_f callback);

    void SetDigitCallback(call_f callback);

    void SetStringCallback(call_f callback);

private:
    call_f start_call = nullptr;
    call_f end_call = nullptr;
    call_f token_call = nullptr;
    call_f digit_call = nullptr;
    call_f string_call = nullptr;
};

#endif //INC_01_TOKEN_PARSER_H
