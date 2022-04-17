#include <gtest/gtest.h>

#include "bigint.hpp"


class TestBigInt : public ::testing::Test {};
class TestBigIntBase : public TestBigInt {};

TEST_F(TestBigIntBase, test_init_no_args)
{
    BigInt num;
}

TEST_F(TestBigIntBase, test_init_int)
{
    BigInt num1(2);
    BigInt num2(45);
    BigInt num3(-12);
    BigInt num4(0);
    BigInt num5(2147483647);
    BigInt num6(-2147483648);
}


TEST_F(TestBigIntBase, test_init_string)
{
    BigInt num1("2");
    BigInt num2("23");
    BigInt num3("124");
    BigInt num4("-1234");
    BigInt num5("0000");
    BigInt num6("");
    BigInt num7("4294967295");
    BigInt num8("4294967296");
    BigInt num9("-4294967296");
    BigInt num10("-4294967297");
    BigInt num11("12423345436356575674684835567468");
}


TEST_F(TestBigIntBase, test_copy)
{
    BigInt num1;
    BigInt num2(num1);
}


int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}