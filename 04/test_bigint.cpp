#include <gtest/gtest.h>

#include "bigint.hpp"


class TestBigInt : public ::testing::Test {};
class TestBigIntBase : public TestBigInt {};

TEST(TestBigIntBase, test_init_no_args)
{
    BigInt num;
}

TEST(TestBigIntBase, test_init_int)
{
    BigInt num1(2);
    BigInt num2(45);
    BigInt num3(-12);
    BigInt num4(0);
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}