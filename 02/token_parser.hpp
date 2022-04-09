#ifndef TOKEN_PARSER_HPP
#define TOKEN_PARSER_HPP

#include <string>
#include <vector>

typedef void (*call_f) ();
typedef void (*call_str_f) (const std::string &);
typedef void (*call_digit_f) (uint64_t);

class TokenParser
{
public:
    TokenParser() = default;
    virtual ~TokenParser() = default;

    void set_start_call(call_f callback);

    void set_end_call(call_f callback);

    void set_token_call(call_str_f callback);

    void set_digit_call(call_digit_f callback);

    void set_string_call(call_str_f callback);

    void parse(const std::string & line);

protected:
    virtual void do_start_call();
    virtual void do_end_call();
    virtual void do_digit_call(uint64_t value);
    virtual void do_token_call(const std::string & token);
    virtual void do_string_call(const std::string & token);

private:
    void do_call(call_str_f callback, const std::string & token);
    void do_call(call_digit_f callback, uint64_t value);
    void do_call(call_f callback);

    void split(const std::string & line);
    bool is_digit_token(const std::string & token);

    uint64_t convert_str_to_unit_64(const std::string & token);

    call_f start_call = nullptr;
    call_f end_call = nullptr;

    call_str_f token_call = nullptr;
    call_str_f string_call = nullptr;

    call_digit_f digit_call = nullptr;

    std::vector<std::string> token_stack;
};

#endif //TOKEN_PARSER_HPP
