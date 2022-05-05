#ifndef HW_CPP_VK_FORMAT_H
#define HW_CPP_VK_FORMAT_H


#include <string>
#include <sstream>
#include <vector>


enum class Error {
    NoError,
    FormatError
};


struct ProcessedFormat
{
    Error make(const std::string & str);

    std::vector<std::string> substrings;
    std::vector<int> arg_num;

private:
    void clear();
    void collect_scope_stat(const std::string & str);
    Error collect_place_stat();

    static bool is_digit_token(const std::string & token);
    static uint64_t convert_str_to_uint_64(const std::string & token);

    enum class Scope
    {
        Open,
        Close
    };

    std::vector<std::pair<Scope, size_t>> scope_stat;
    std::vector<std::pair<size_t, size_t>> place_stat;
};


template<class... ArgsT>
std::string format(const std::string & str, const ArgsT & ...args)
{

}


#endif //HW_CPP_VK_FORMAT_H
