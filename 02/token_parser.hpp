#ifndef INC_01_TOKEN_PARSER_H
#define INC_01_TOKEN_PARSER_H

#include <string>
#include <vector>

typedef void (*call_f) ();
typedef void (*call_str_f) (const std::string &);

class TokenParser
{
public:
    TokenParser() = default;
    virtual ~TokenParser() = default;

    void set_start_call(call_f callback);

    void set_end_call(call_f callback);

    void set_token_call(call_str_f callback);

    void set_digit_call(call_str_f callback);

    void set_string_call(call_str_f callback);

    void parse(const std::string & line);

protected:
    virtual void do_start_call();
    virtual void do_end_call();
    virtual void do_token_call(const std::string & token);
    virtual void do_digit_call(const std::string & token);
    virtual void do_string_call(const std::string & token);

private:
    void do_call(call_str_f callback, const std::string & token);
    void do_call(call_f callback);

    void split(const std::string & line);
    bool is_digit_token(const std::string & token);

    call_f start_call = nullptr;
    call_f end_call = nullptr;

    call_str_f token_call = nullptr;
    call_str_f digit_call = nullptr;
    call_str_f string_call = nullptr;

    std::vector<std::string> token_stack;
};

#endif //INC_01_TOKEN_PARSER_H
