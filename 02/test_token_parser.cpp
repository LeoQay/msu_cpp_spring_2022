#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "token_parser.hpp"


class MockTokenParser : public TokenParser
{
public:
    MOCK_METHOD((void), do_start_call, (), (override));
    MOCK_METHOD((void), do_end_call, (), (override));
    MOCK_METHOD((void), do_string_call, (const std::string &), (override));
    MOCK_METHOD((void), do_digit_call, (const std::string &), (override));
    MOCK_METHOD((void), do_token_call, (const std::string &), (override));
};


class TestTokenParser : public ::testing::Test
{
public:

};

TEST_F(TestTokenParser, test_simple)
{
    MockTokenParser parser;
    EXPECT_CALL(parser, do_start_call()).Times(1);
    EXPECT_CALL(parser, do_end_call()).Times(1);
    EXPECT_CALL(parser, do_string_call("text")).Times(1);
    EXPECT_CALL(parser, do_string_call("Some")).Times(1);
    EXPECT_CALL(parser, do_token_call("text")).Times(1);;
    EXPECT_CALL(parser, do_token_call("Some")).Times(1);

    parser.parse("Some text");
}


int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
