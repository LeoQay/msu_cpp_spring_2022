#include <string>
#include <sstream>
#include <gtest/gtest.h>

#include "bigint.hpp"


class TestBigInt : public ::testing::Test
{
public:
    static void cmp(const BigInt & obj, const std::string & s);
};


class TestBigIntInit : public TestBigInt {};


class TestBigIntInitNoArgs : public TestBigIntInit {};

class TestBigIntInitInt : public TestBigIntInit {};

class TestBigIntInitStr : public TestBigIntInit {};

class TestBigIntInitCopy : public TestBigIntInit {};

class TestBigIntInitMove : public TestBigIntInit
{
public:
    static BigInt for_test_move_1();
    static BigInt for_test_move_2();
    static BigInt for_test_move_3();
    static BigInt for_test_move_4(BigInt & obj);
    static BigInt for_test_move_5();
    static BigInt for_test_move_6();
};

class TestBigIntEQ : public TestBigInt {};


void TestBigInt::cmp(const BigInt & obj, const std::string & s)
{
    std::stringstream stream;
    stream << obj;
    std::string str = stream.str();
    ASSERT_EQ(str, s);
}


TEST_F(TestBigIntInitNoArgs, test_init_no_args_1)
{
    BigInt num;
    cmp(num, "0");
}


TEST_F(TestBigIntInitInt, test_init_int_1)
{
    BigInt num1(2);
    cmp(num1, "2");
}

TEST_F(TestBigIntInitInt, test_init_int_2)
{
    BigInt num2(45);
    cmp(num2, "45");
}

TEST_F(TestBigIntInitInt, test_init_int_3)
{
    BigInt num3(-12);
    cmp(num3, "-12");
}

TEST_F(TestBigIntInitInt, test_init_int_4)
{
    BigInt num4(0);
    cmp(num4, "0");
}

TEST_F(TestBigIntInitInt, test_init_int_5)
{
    BigInt num5(2147483647);
    cmp(num5, "2147483647");
}

TEST_F(TestBigIntInitInt, test_init_int_6)
{
    BigInt num6(-2147483648);
    cmp(num6, "-2147483648");
}


TEST_F(TestBigIntInitStr, test_init_str_1)
{
    BigInt num1("2");
    cmp(num1, "2");
}

TEST_F(TestBigIntInitStr, test_init_str_2)
{
    BigInt num2("23");
    cmp(num2, "23");
}

TEST_F(TestBigIntInitStr, test_init_str_3)
{
    BigInt num3("124");
    cmp(num3, "124");
}

TEST_F(TestBigIntInitStr, test_init_str_4)
{
    BigInt num4("-1234");
    cmp(num4, "-1234");
}

TEST_F(TestBigIntInitStr, test_init_str_5)
{
    BigInt num5("0000");
    cmp(num5, "0");
}

TEST_F(TestBigIntInitStr, test_init_str_6)
{
    BigInt num6("");
    cmp(num6, "0");
}

TEST_F(TestBigIntInitStr, test_init_str_7)
{
    BigInt num7("4294967295");
    cmp(num7, "4294967295");
}

TEST_F(TestBigIntInitStr, test_init_str_8)
{
    BigInt num8("4294967296");
    cmp(num8, "4294967296");
}

TEST_F(TestBigIntInitStr, test_init_str_9)
{
    BigInt num9("-4294967296");
    cmp(num9, "-4294967296");
}

TEST_F(TestBigIntInitStr, test_init_str_10)
{
    BigInt num10("-4294967297");
    cmp(num10, "-4294967297");
}

TEST_F(TestBigIntInitStr, test_init_str_11)
{
    BigInt num11("12423345436356575674684835567468");
    cmp(num11, "12423345436356575674684835567468");
}


TEST_F(TestBigIntInitCopy, test_copy_1)
{
    BigInt num1;
    BigInt num2(num1);
    cmp(num2, "0");
    cmp(num1, "0");
}

TEST_F(TestBigIntInitCopy, test_copy_2)
{
    BigInt num1 = 234346;
    cmp(num1, "234346");
    BigInt num2 = num1;
    cmp(num2, "234346");
    cmp(num1, "234346");
}

TEST_F(TestBigIntInitCopy, test_copy_3)
{
    BigInt num1 = BigInt("2545847634758378365");
    cmp(num1, "2545847634758378365");
    BigInt num2 = num1;
    cmp(num1, "2545847634758378365");
    cmp(num2, "2545847634758378365");
}

TEST_F(TestBigIntInitCopy, test_copy_4)
{
    BigInt num1 = -124124;
    BigInt num2 = num1;
    cmp(num1, "-124124");
    cmp(num2, "-124124");

    num1 = BigInt("16545323254657");
    num1 = num1;
    num2 = num2;
    cmp(num1, "16545323254657");
    cmp(num2, "-124124");
}


BigInt TestBigIntInitMove::for_test_move_1()
{
    BigInt num = 1245;
    return num;
}

TEST_F(TestBigIntInitMove, test_move_1)
{
    BigInt num;
    num = for_test_move_1();
    cmp(num, "1245");
}

BigInt TestBigIntInitMove::for_test_move_2()
{
    BigInt num;
    return num;
}

TEST_F(TestBigIntInitMove, test_move_2)
{
    BigInt num;
    num = for_test_move_2();
    cmp(num, "0");
}

BigInt TestBigIntInitMove::for_test_move_3()
{
    BigInt num("-124235534235243");
    return num;
}

TEST_F(TestBigIntInitMove, test_move_3)
{
    BigInt num;
    num = for_test_move_3();
    cmp(num, "-124235534235243");
    num = for_test_move_4(num);
    cmp(num, "-124235534235243");
}

BigInt TestBigIntInitMove::for_test_move_4(BigInt & obj)
{
    return obj;
}

TEST_F(TestBigIntInitMove, test_move_4)
{
    BigInt num("-124235534235243");
    num = for_test_move_4(num);
    cmp(num, "-124235534235243");
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
