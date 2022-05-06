#include <gtest/gtest.h>

#include "format.hpp"


class TestFormat : public ::testing::Test {};


TEST_F(TestFormat, test_no_scopes_no_args)
{
    std::string to_format = "Some string";
    auto result = format(to_format);
    ASSERT_EQ(to_format, result);
}


int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
