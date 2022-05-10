#include <gtest/gtest.h>

#include "format.hpp"


class TestFormat : public ::testing::Test
{
public:
    template<class ExpectedErrorT, class... ArgsT>
    void bad_format(const std::string & to_format, const ArgsT & ...args)
    {
        try {
            format(to_format, args...);
        }
        catch (ExpectedErrorT & err)
        {
            return;
        }
        catch (FormatException & err)
        {
            ASSERT_EQ(err.what(), "");
            return;
        }
        catch (...)
        {
            ASSERT_EQ("Unexpected error, error must be inherit "
                      "by FormatException", "");
            return;
        }
        ASSERT_EQ("Exception hasn\'t been thrown", "");
    }
};


TEST_F(TestFormat, test_default)
{
    ASSERT_EQ("one+one = 2",
              format("{1}+{1} = {0}",
                     2, "one"));
}


TEST_F(TestFormat, test_no_scopes_no_args)
{
    ASSERT_EQ("Some string",
              format("Some string"));
}


TEST_F(TestFormat, test_no_scopes_some_args)
{
    ASSERT_EQ("Some string",
              format("Some string",
                     "124", 3, true));
}


TEST_F(TestFormat, test_some_scopes_no_args_1)
{
    bad_format<ArgsAmountFormatException>(
    "Some string with {0}");
}


TEST_F(TestFormat, test_some_scopes_no_args_2)
{
    bad_format<ArgsAmountFormatException>(
    "Some string with {1} and with {0}");
}


TEST_F(TestFormat, test_one_scope_one_arg_1)
{
    ASSERT_EQ("ARG0",
              format("{0}",
                     "ARG0"));
}


TEST_F(TestFormat, test_one_scope_one_arg_2)
{
    ASSERT_EQ("Some text and ARG0 and another text",
              format("Some text and {0} and another text",
                     "ARG0"));
}


TEST_F(TestFormat, test_more_scopes_than_args_1)
{
    bad_format<ArgsAmountFormatException>(
    "Qwerty {1} {0} lala",
    "I am only one");
}


TEST_F(TestFormat, test_more_scopes_than_args_2)
{
    bad_format<ArgsAmountFormatException>("{10}",
               "Arg0", "Arg1", "Arg2", 3, 4);
}


TEST_F(TestFormat, test_reverse_1)
{
    ASSERT_EQ("Arg3 Arg2 Arg1 Arg0",
              format("{3} {2} {1} {0}",
                     "Arg0", "Arg1", "Arg2", "Arg3"));
}

TEST_F(TestFormat, test_reverse_2)
{
    ASSERT_EQ("Arg0 Arg3 Arg2 Arg1",
              format("{0} {3} {2} {1}",
                     "Arg0", "Arg1", "Arg2", "Arg3"));
}


TEST_F(TestFormat, test_bad_scopes_1)
{
    bad_format<ScopeFormatException>("}");
    bad_format<ScopeFormatException>("{ ery", 2, 1);
    bad_format<ScopeFormatException>("}");
    bad_format<ScopeFormatException>("{0", "arg", 0, 1, 2);
    bad_format<ScopeFormatException>("rdh }0 hr");
    bad_format<ScopeFormatException>("{0 rh", 6);
    bad_format<ScopeFormatException>("wet 0}");
}


TEST_F(TestFormat, test_bad_scopes_2)
{
    bad_format<ArgLexFormatException>("{}0", "arg", 0, 1, 2);
    bad_format<ScopeFormatException>("}0{");
    bad_format<ArgLexFormatException>("0{}", "Arg");
    bad_format<ScopeFormatException>("rjst {0{");
    bad_format<ScopeFormatException>("reherj }0}  drh");
}


TEST_F(TestFormat, test_bad_arg_lex)
{
    bad_format<ArgLexFormatException>("{a}", 2, 3);
    bad_format<ArgLexFormatException>(
    "Haha, {0} and {-1}",
    "Arg-1", "Arg0");
}


TEST_F(TestFormat, test_repeat_1)
{
    ASSERT_EQ("Arg0 or not Arg1 or Arg1 or not Arg0",
              format("{0} or not {1} or {1} or not {0}",
                     "Arg0", "Arg1"));
}


TEST_F(TestFormat, test_repeat_2_and_only_scopes)
{
    ASSERT_EQ("ArgumentArgumentArgumentArgument",
              format("{0}{0}{0}{0}",
                     "Argument", 2, true, 3));

    ASSERT_EQ("2222",
              format("{1}{1}{1}{1}",
                     "Argument", 2, true, 3));

    ASSERT_EQ("3333",
              format("{3}{3}{3}{3}",
                     "Argument", 2, true, 3));
}


int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
