#include <algorithm>
#include <cstring>
#include <iomanip>
#include <stdexcept>

#include "bigint.hpp"


BigInt::~BigInt()
{
    delete [] ptr;
}


BigInt::BigInt()
{
    make_zero();
}


BigInt::BigInt(const BigInt & other)
{
    is_minus = other.is_minus;
    len = other.len;
    real_len = len + offset;
    ptr = new uint32_t [real_len];
    memcpy(ptr, other.ptr, len * sizeof *ptr);
}


BigInt & BigInt::operator= (const BigInt & other)
{
    if (this == &other)
    {
        return *this;
    }

    delete [] ptr;

    is_minus = other.is_minus;
    len = other.len;
    real_len = len + offset;
    ptr = new uint32_t [real_len];
    memcpy(ptr, other.ptr, len * sizeof *ptr);

    return *this;
}


BigInt::BigInt(BigInt && other) noexcept
{
    is_minus = other.is_minus;
    real_len = other.real_len;
    len = other.len;
    ptr = other.ptr;

    other.real_len = 0;
    other.len = 0;
    other.ptr = nullptr;
}


BigInt & BigInt::operator= (BigInt && other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    delete [] ptr;

    is_minus = other.is_minus;
    real_len = other.real_len;
    len = other.len;
    ptr = other.ptr;

    other.real_len = 0;
    other.len = 0;
    other.ptr = nullptr;

    return *this;
}


BigInt::BigInt(int32_t value)
{
    if (value == 0)
    {
        len = 1;
        real_len = 1 + offset;
        ptr = new uint32_t [real_len];
        ptr[0] = 0;
        return;
    }

    int64_t ext = value;

    if (ext < 0)
    {
        is_minus = true;
        ext *= -1;
    }

    int count = digit_num(ext, base);

    len = count;
    real_len = count + offset;
    ptr = new uint32_t [real_len];

    size_t i = 0;
    while (ext > 0)
    {
        ptr[i++] = ext % base;
        ext /= base;
    }
}


BigInt::BigInt(const std::string & str)
{
    std::string str_copy = str;

    if (str.empty())
    {
        make_zero();
        return;
    }

    if (!check_num_token(str))
    {
        throw std::bad_exception();
    }

    if (str[0] == '-')
    {
        is_minus = true;
        str_copy.erase(0, 1);
    }

    size_t start = 0, size = str_copy.size();
    while (start != size && str_copy[0] == '0')
    {
        start++;
    }
    str_copy.substr(0, start);

    if (str_copy.empty())
    {
        make_zero();
        return;
    }

    len = (8 + str_copy.size()) / 9;
    real_len = len + offset;
    ptr = new uint32_t [real_len];

    for (size_t i = 0; i != len; i++)
    {
        size_t size = str_copy.size();
        size_t pos = size >= 9 ? size - 9 : 0;
        ptr[i] = str_to_uint(str_copy.substr(pos));
        str_copy.erase(pos);
    }
}


bool BigInt::check_num_token(const std::string & str)
{
    size_t size = str.size();

    if (size == 0)
    {
        return false;
    }

    if (size == 1)
    {
        return std::isdigit(str[0]);
    }

    size_t start = str[0] == '-' ? 1 : 0;

    for (size_t i = start; i != size; i++)
    {
        if (!std::isdigit(str[i]))
        {
            return false;
        }
    }

    return true;
}


BigInt & BigInt::operator-()
{
    check_none();

    is_minus = !is_minus;
    return *this;
}


BigInt BigInt::operator+ (const BigInt & other) const
{
    check_none();
    other.check_none();

    if (is_minus == other.is_minus)
    {
        BigInt result = add(other);
        result.is_minus = is_minus;
        return result;
    }
    else if (large(other))
    {
        BigInt result = sub(other);
        result.is_minus = is_minus;
        return result;
    }
    else
    {
        BigInt result = other.sub(*this);
        result.is_minus = other.is_minus;
        return result;
    }
}


BigInt BigInt::operator- (const BigInt & other) const
{
    check_none();
    other.check_none();

    if (is_minus != other.is_minus)
    {
        BigInt result = add(other);
        result.is_minus = is_minus;
        return result;
    }
    else if (large(other))
    {
        BigInt result = sub(other);
        result.is_minus = is_minus;
        return result;
    }
    else
    {
        BigInt result = other.sub(*this);
        result.is_minus = !is_minus;
        return result;
    }
}


void BigInt::check_none() const
{
    if (ptr == nullptr || len == 0 || real_len == 0)
    {
        throw std::bad_exception();
    }
}


void BigInt::make_zero()
{
    delete [] ptr;
    len = 1;
    real_len = 1 + offset;
    ptr = new uint32_t [real_len];
    ptr[0] = 0;
}


int BigInt::digit_num(uint32_t value, uint32_t _base)
{
    int count = 0;

    while (value != 0)
    {
        value /= _base;
        count++;
    }

    return count;
}


uint32_t BigInt::str_to_uint(const std::string & str)
{
    uint32_t result = 0;

    for (char sym : str)
    {
        result = 10 * result + (sym - '0');
    }

    return result;
}


BigInt BigInt::add(const BigInt & other) const
{
    BigInt result;

    delete [] result.ptr;
    result.real_len = std::max(len, other.len) + offset;
    result.ptr = new uint32_t [result.real_len];
    result.len = low_add(result.ptr,
                         ptr, len, other.ptr, other.len);

    return result;
}


BigInt BigInt::sub(const BigInt & other) const
{
    BigInt result;

    delete [] result.ptr;
    result.real_len = std::max(len, other.len);
    result.ptr = new uint32_t [result.real_len];
    result.len = low_sub(
    result.ptr,ptr, len, other.ptr, other.len);

    result.cut_zeros();

    return result;
}


size_t BigInt::low_add(uint32_t * dest,
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


size_t BigInt::low_sub(uint32_t * dest,
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
        while (a[p] == 0)
        {
            dest[p] = base_1;
            p++;
        }
    }

    for (size_t i = p; i != len_a; i++)
    {
        dest[i] = a[i];
    }

    dest[p]--;

    return len_a;
}


std::ostream & operator<< (std::ostream & stream, const BigInt & num)
{
    if (num.is_minus)
    {
        stream << '-';
    }

    auto ptr = num.ptr;
    size_t n = num.len;

    if (n == 0)
    {
        return stream;
    }

    stream << ptr[n - 1];

    if (n == 1)
    {
        stream << std::endl;
        return stream;
    }

    stream << std::setfill('0');

    for (size_t i = 1; i != n; i++)
    {
        stream << std::setw(num.digits);
        stream << ptr[n - i - 1];
    }

    stream << std::setfill(' ');

    stream << std::endl;

    return stream;
}


void BigInt::cut_zeros()
{
    if (len <= 1)
    {
        return;
    }

    while (len > 1 && ptr[len - 1] == 0)
    {
        len--;
    }
}


bool BigInt::large(const BigInt & other) const
{
    if (len != other.len)
    {
        return len > other.len;
    }

    for (size_t i = 0; i != len; i++)
    {
        if (ptr[len - i - 1] != other.ptr[len - i - 1])
        {
            return ptr[len - i - 1] > other.ptr[len - i - 1];
        }
    }

    return false;
}

bool BigInt::equal(const BigInt & other) const
{
    if (len != other.len)
    {
        return false;
    }

    for (size_t i = 0; i != len; i++)
    {
        if (ptr[len - i - 1] != other.ptr[len - i - 1])
        {
            return false;
        }
    }

    return true;
}

