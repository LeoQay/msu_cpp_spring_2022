#include <string>
#include <sstream>
#include <gtest/gtest.h>

#include "bigint.hpp"


class TestBigInt : public ::testing::Test
{
public:
    static void cmp(const BigInt & obj, const std::string & s);
};


class TestBigIntBase : public TestBigInt {};
class TestBigIntEQ : public TestBigInt {};


void TestBigInt::cmp(const BigInt & obj, const std::string & s)
{
    std::stringstream stream;
    stream << obj;
    std::string str = stream.str();
    ASSERT_EQ(str, s);
}


TEST_F(TestBigIntBase, test_init_no_args)
{
    BigInt num;
    cmp(num, "0");
}


TEST_F(TestBigIntBase, test_init_int)
{
    BigInt num1(2);
    cmp(num1, "2");
    BigInt num2(45);
    cmp(num2, "45");
    BigInt num3(-12);
    cmp(num3, "-12");
    BigInt num4(0);
    cmp(num4, "0");
    BigInt num5(2147483647);
    cmp(num5, "2147483647");
    BigInt num6(-2147483648);
    cmp(num6, "-2147483648");
}


TEST_F(TestBigIntBase, test_init_string)
{
    BigInt num1("2");
    cmp(num1, "2");
    BigInt num2("23");
    cmp(num2, "23");
    BigInt num3("124");
    cmp(num3, "124");
    BigInt num4("-1234");
    cmp(num4, "-1234");
    BigInt num5("0000");
    cmp(num5, "0");
    BigInt num6("");
    cmp(num6, "0");
    BigInt num7("4294967295");
    cmp(num7, "4294967295");
    BigInt num8("4294967296");
    cmp(num8, "4294967296");
    BigInt num9("-4294967296");
    cmp(num9, "-4294967296");
    BigInt num10("-4294967297");
    cmp(num10, "-4294967297");
    BigInt num11("12423345436356575674684835567468");
    cmp(num11, "12423345436356575674684835567468");
}


TEST_F(TestBigIntBase, test_copy)
{
    try {
        BigInt num1;
        BigInt num2(num1);
        num1 = 234346;
        num2 = num1;
        num1 = BigInt("2545847634758378365");
        num2 = num1;
    }
    catch (...)
    {
        ASSERT_TRUE(false);
    }
}


TEST_F(TestBigIntEQ, test_eq_1)
{
    BigInt num1, num2 = 0;
    ASSERT_TRUE(num1 == num2);
}


TEST_F(TestBigIntEQ, test_eq_2)
{
    BigInt num1 = 123, num2 = -123;
    ASSERT_FALSE(num1 == num2);
}


TEST_F(TestBigIntEQ, test_eq_3)
{
    BigInt num1("123456789987654321"), num2("123456789987654321");
    ASSERT_TRUE(num1 == num2);
}


TEST_F(TestBigIntEQ, test_eq_4)
{
    BigInt num1("-987654321123456789987654321");
    BigInt num2("987654321123456789987654321");
    ASSERT_FALSE(num1 == num2);
}


int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
