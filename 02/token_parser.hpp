#ifndef INC_01_TOKEN_PARSER_H
#define INC_01_TOKEN_PARSER_H

#include <string>
#include <vector>

typedef void (*call_f) ();
typedef void (*call_str_f) (std::string &);

class TokenParser
{
public:
    TokenParser() = default;

    void SetStartCallback(call_f callback);

    void SetEndCallback(call_f callback);

    void SetTokenCallback(call_str_f callback);

    void SetDigitCallback(call_str_f callback);

    void SetStringCallback(call_str_f callback);

    void Parse(const std::string & line);

private:

    void split(const std::string & line);

    void do_call(call_str_f callback, std::string & token);
    void do_call(call_f callback);

    bool is_digit_token(const std::string & token);

    call_f start_call = nullptr;
    call_f end_call = nullptr;

    call_str_f token_call = nullptr;
    call_str_f digit_call = nullptr;
    call_str_f string_call = nullptr;

    std::vector<std::string> token_stack;
};

#endif //INC_01_TOKEN_PARSER_H
