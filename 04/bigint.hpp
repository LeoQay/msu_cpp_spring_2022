#ifndef MSU_CPP_SPRING_2022_BIGINT_H
#define MSU_CPP_SPRING_2022_BIGINT_H

#include <iostream>
#include <string>


class BigInt
{
public:
    BigInt();
    BigInt(int32_t value);
    BigInt(const std::string & str);
    virtual ~BigInt();

    BigInt(const BigInt & other);
    BigInt & operator= (const BigInt & other);

    BigInt(BigInt && other);
    BigInt & operator= (BigInt && other);

    BigInt & operator-(int);

    bool operator== (const BigInt & other) const;
    bool operator!= (const BigInt & other) const;
    bool operator> (const BigInt & other) const;
    bool operator<= (const BigInt & other) const;
    bool operator< (const BigInt & other) const;
    bool operator>= (const BigInt & other) const;

    BigInt & operator+= (const BigInt & other);
    BigInt & operator+= (int32_t value);

    BigInt operator+ (const BigInt & other) const;
    BigInt operator+ (int32_t value) const;

    friend BigInt operator+ (int32_t value, const BigInt & other);

    BigInt & operator-= (const BigInt & other);
    BigInt & operator-= (int32_t value);

    BigInt operator- (const BigInt & other) const;
    BigInt operator- (int32_t value) const;

    friend BigInt operator- (int32_t value, const BigInt & other);

    BigInt & operator*= (const BigInt & other);
    BigInt & operator*= (int32_t value);

    BigInt operator* (const BigInt & other) const;
    BigInt operator* (int32_t value) const;

    friend BigInt operator* (int32_t value, const BigInt & other);

    friend std::ostream & operator<< (std::ostream & stream, const BigInt & num);
private:

    // dest, a, b - могут быть одним адресом
    // Ожидает, что по адресу dest места не меньше, чем 1 + max(len_a, len_b)
    size_t add(uint32_t * dest,
               const uint32_t * a, size_t len_a,
               const uint32_t * b, size_t len_b) const;

    // dest, a, b - могут быть одним адресом
    // Ожидает, что по адресу dest места не меньше, чем max(len_a, len_b)
    // Ожидает, что a >= b
    size_t sub(uint32_t * dest,
               const uint32_t * a, size_t len_a,
               const uint32_t * b, size_t len_b) const;

    uint32_t * ptr = nullptr;
    size_t len = 0;
    size_t real_len = 0;
    bool is_minus = false;

    // 2 * (basis ^ power) < 2 ^ 32
    int basis = 10;
    int power = 9;
    uint32_t base;
};


#endif //MSU_CPP_SPRING_2022_BIGINT_H
