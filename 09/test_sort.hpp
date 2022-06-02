#ifndef HW_CPP_VK_TEST_SORT_HPP
#define HW_CPP_VK_TEST_SORT_HPP

#include <string>
#include <cstdio>
#include <random>
#include <limits>


class Generator
{
public:
    static const size_t buf_size = 65536;

    // size - amount of value of type int64_t
    static void gen(const std::string & name, size_t size)
    {
        FILE * file = fopen64(name.c_str(), "wb");

        std::random_device rd;
        std::mt19937 generator(rd());

        int64_t buffer[buf_size];

        for (size_t i = 0; i < size / buf_size; i++)
        {
            for (long & it : buffer)
            {
                it = static_cast<int64_t>(generator());
            }

            std::fwrite(buffer, sizeof(int64_t), buf_size, file);
        }

        auto r = size % buf_size;

        if (r != 0)
        {
            for (size_t i = 0; i < r; i++)
            {
                buffer[i] = static_cast<int64_t>(generator());
            }

            std::fwrite(buffer, sizeof(int64_t), r, file);
        }

        std::fclose(file);
    }
};


class SortChecker
{
public:
    static const size_t buf_size = 65536;

    static bool check(const std::string & name)
    {
        FILE * file = fopen64(name.c_str(), "rb");

        int64_t buffer[buf_size];
        int64_t prev = std::numeric_limits<int64_t>::min();

        try {
            while (true)
            {
                auto len = std::fread(buffer, sizeof(int64_t), buf_size, file);
                if (len == 0) break;
                if (prev > buffer[0]) throw std::exception();
                for (size_t i = 0; i < len - 1; i++)
                {
                    if (buffer[i] > buffer[i + 1]) throw std::exception();
                }
                prev = buffer[len - 1];
            }
        }
        catch (std::exception &)
        {
            std::fclose(file);
            return false;
        }

        std::fclose(file);
        return true;
    }
};


#endif //HW_CPP_VK_TEST_SORT_HPP
