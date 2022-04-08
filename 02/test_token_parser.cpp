#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "token_parser.hpp"


class MockTokenParser : public TokenParser
{
public:
    MOCK_METHOD(void, do_start_call, (), (override));
    MOCK_METHOD(void, do_end_call, (), (override));
    MOCK_METHOD(void, do_string_call, (const std::string &), (override));
    MOCK_METHOD(void, do_digit_call, (const std::string &), (override));
    MOCK_METHOD(void, do_token_call, (const std::string &), (override));
};


class TestTokenParser : public ::testing::Test
{
public:

};

TEST_F(TestTokenParser, test_gmock_test)
{
    MockTokenParser parser;

    EXPECT_CALL(parser, do_start_call()).Times(1);
    EXPECT_CALL(parser, do_end_call()).Times(1);
    EXPECT_CALL(parser, do_string_call("text")).Times(1);
    EXPECT_CALL(parser, do_string_call("Some")).Times(1);
    EXPECT_CALL(parser, do_token_call("text")).Times(1);
    EXPECT_CALL(parser, do_token_call("Some")).Times(1);

    parser.parse("Some text");
}

TEST_F(TestTokenParser, test_empty)
{
    MockTokenParser parser;

    EXPECT_CALL(parser, do_start_call()).Times(1);
    EXPECT_CALL(parser, do_end_call()).Times(1);

    parser.parse("");
}

TEST_F(TestTokenParser, test_one_string)
{
    MockTokenParser parser;

    EXPECT_CALL(parser, do_start_call()).Times(1);
    EXPECT_CALL(parser, do_end_call()).Times(1);
    EXPECT_CALL(parser, do_token_call("String")).Times(1);
    EXPECT_CALL(parser, do_string_call("String")).Times(1);

    parser.parse("String");
}

TEST_F(TestTokenParser, test_one_digit)
{
    MockTokenParser parser;

    EXPECT_CALL(parser, do_start_call()).Times(1);
    EXPECT_CALL(parser, do_end_call()).Times(1);
    EXPECT_CALL(parser, do_token_call("123")).Times(1);
    EXPECT_CALL(parser, do_digit_call("123")).Times(1);

    parser.parse("123");
}

TEST_F(TestTokenParser, test_digit_and_string_simple)
{
    MockTokenParser parser;

    EXPECT_CALL(parser, do_start_call()).Times(1);
    EXPECT_CALL(parser, do_end_call()).Times(1);
    EXPECT_CALL(parser, do_digit_call("1204")).Times(1);
    EXPECT_CALL(parser, do_token_call("1204")).Times(1);
    EXPECT_CALL(parser, do_string_call("string")).Times(1);
    EXPECT_CALL(parser, do_token_call("string")).Times(1);

    parser.parse("string 1204");
}

TEST_F(TestTokenParser, test_digit_and_string_many_spaces)
{
    MockTokenParser parser;

    EXPECT_CALL(parser, do_start_call()).Times(1);
    EXPECT_CALL(parser, do_end_call()).Times(1);
    EXPECT_CALL(parser, do_digit_call("309234")).Times(1);
    EXPECT_CALL(parser, do_token_call("309234")).Times(1);
    EXPECT_CALL(parser, do_string_call("some_string_token")).Times(1);
    EXPECT_CALL(parser, do_token_call("some_string_token")).Times(1);

    parser.parse(" \n  \n \t  some_string_token  \n\n  \t \t 309234 \n\t ");
}

TEST_F(TestTokenParser, test_digit_limits)
{
    MockTokenParser parser;

    EXPECT_CALL(parser, do_start_call()).Times(1);
    EXPECT_CALL(parser, do_end_call()).Times(1);

    EXPECT_CALL(parser, do_token_call("18446744073709551615")).Times(1);
    EXPECT_CALL(parser, do_token_call("18446744073709551616")).Times(1);
    EXPECT_CALL(parser, do_token_call("0")).Times(1);
    EXPECT_CALL(parser, do_token_call("-12")).Times(1);
    EXPECT_CALL(parser, do_token_call("-1")).Times(1);

    EXPECT_CALL(parser, do_digit_call("18446744073709551615")).Times(1);
    EXPECT_CALL(parser, do_digit_call("18446744073709551616")).Times(0);
    EXPECT_CALL(parser, do_digit_call("0")).Times(1);
    EXPECT_CALL(parser, do_digit_call("-12")).Times(0);
    EXPECT_CALL(parser, do_digit_call("-1")).Times(0);

    EXPECT_CALL(parser, do_string_call("18446744073709551615")).Times(0);
    EXPECT_CALL(parser, do_string_call("18446744073709551616")).Times(1);
    EXPECT_CALL(parser, do_string_call("0")).Times(0);
    EXPECT_CALL(parser, do_string_call("-12")).Times(1);
    EXPECT_CALL(parser, do_string_call("-1")).Times(1);

    parser.parse("18446744073709551615 18446744073709551616 0 -12 -1");
}

TEST_F(TestTokenParser, test_many_strings)
{
    MockTokenParser parser;

    EXPECT_CALL(parser, do_start_call()).Times(1);
    EXPECT_CALL(parser, do_end_call()).Times(1);

    EXPECT_CALL(parser, do_token_call("str")).Times(1);
    EXPECT_CALL(parser, do_string_call("str")).Times(1);
    EXPECT_CALL(parser, do_token_call("der")).Times(1);
    EXPECT_CALL(parser, do_string_call("der")).Times(1);
    EXPECT_CALL(parser, do_token_call("wer")).Times(1);
    EXPECT_CALL(parser, do_string_call("wer")).Times(1);
    EXPECT_CALL(parser, do_token_call("er")).Times(1);
    EXPECT_CALL(parser, do_string_call("er")).Times(1);
    EXPECT_CALL(parser, do_token_call("qwr")).Times(1);
    EXPECT_CALL(parser, do_string_call("qwr")).Times(1);

    parser.parse("  str  der  wer  er qwr  ");
}



int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
