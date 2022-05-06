#ifndef HW_CPP_VK_PROCESSED_FORMAT_HPP
#define HW_CPP_VK_PROCESSED_FORMAT_HPP


#include <string>
#include <sstream>
#include <vector>


struct ProcessedFormat
{
    void make(const std::string & str);

    std::vector<std::string> substrings;
    std::vector<size_t> arg_num;

private:
    void clear_service();
    void clear_target();
    void collect_scope_stat(const std::string & str);
    void collect_place_stat();
    void build_target(const std::string & str);

    static std::string & strip(std::string & str);
    static bool is_digit_token(const std::string & token);
    static uint64_t str_to_uint(const std::string & token);

    enum class Scope
    {
        Open,
        Close
    };

    std::vector<std::pair<Scope, size_t>> scope_stat;
    std::vector<std::pair<size_t, size_t>> place_stat;
};



#endif //HW_CPP_VK_PROCESSED_FORMAT_HPP
