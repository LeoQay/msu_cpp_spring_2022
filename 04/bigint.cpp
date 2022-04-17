#include <algorithm>
#include <cstring>

#include "bigint.hpp"


BigInt::BigInt(int32_t value)
{
    base = 1;
    for (auto i = 0; i != power; i++)
    {
        base *= basis;
    }

    int64_t ext = value;

    if (ext < 0)
    {
        is_minus = true;
        ext *= -1;
    }


}


size_t BigInt::add(uint32_t * dest,
                   const uint32_t * a, size_t len_a,
                   const uint32_t * b, size_t len_b) const
{
    uint32_t r = 0;
    size_t n = std::min(len_a, len_b);
    size_t max_n = std::max(len_a, len_b);

    for (size_t i = 0; i != n; i++)
    {
        uint32_t sum = a[i] + b[i] + r;
        r = sum / base;
        dest[i] = sum % base;
    }

    if (len_a == len_b)
    {
        if (r != 0)
        {
            dest[n] = r;
            return max_n + 1;
        }
        return max_n;
    }

    const uint32_t * src = len_a > len_b ? a : b;

    for (size_t i = n; i != max_n; i++)
    {
        uint32_t sum = src[i] + r;
        r = sum / base;
        dest[i] = sum % base;
    }

    if (r != 0)
    {
        dest[max_n] = r;
        return max_n + 1;
    }
    return max_n;
}


size_t BigInt::sub(uint32_t * dest,
                   const uint32_t * a, size_t len_a,
                   const uint32_t * b, size_t len_b) const
{
    auto base_1 = base - 1;

    bool flag = false;

    for (size_t i = 0; i != len_b;)
    {
        if (a[i] < b[i])
        {
            dest[i] = base + a[i] - b[i];

            i++;
            while (i != len_b && a[i] == 0)
            {
                dest[i] = base_1 - b[i];
                i++;
            }

            if (i == len_b)
            {
                flag = true;
            }
        }
        else
        {
            dest[i] = a[i] - b[i];
            i++;
        }
    }

    if (len_a == len_b)
    {
        return len_b;
    }

    size_t p = len_b;

    if (flag)
    {
        while (p != len_a && a[p] == 0)
        {
            dest[p] = base_1;
            p++;
        }

    }

    for (size_t i = p; i != len_a; i++)
    {
        dest[i] = a[i];
    }

    return len_a;
}

std::ostream & operator<< (std::ostream & stream, const BigInt & num)
{
    if (num.is_minus)
    {
        stream << '-';
    }

    if (num.len == 0)
    {
        return stream;
    }

    auto ptr = num.ptr;
    size_t n = num.len - 1;

    for (size_t i = n; i != 0; i--)
    {
        stream << ptr[i];
    }

    stream << std::endl;

    return stream;
}
