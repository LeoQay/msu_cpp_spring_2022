#include <gtest/gtest.h>

#include "format.hpp"


class TestFormat : public ::testing::Test
{
public:
    template<class ExpectedErrorT, class... ArgsT>
    void bad_format(
        const std::string & msg,
        const std::string & to_format,  const ArgsT & ...args)
    {
        try {
            format(to_format, args...);
        }
        catch (ExpectedErrorT & err)
        {
            ASSERT_EQ(std::string(err.what()), msg);
            return;
        }
        catch (FormatException & err)
        {
            ASSERT_EQ(std::string(err.what()), std::string(""));
            return;
        }
        catch (...)
        {
            ASSERT_EQ(
                std::string(
                    "Unexpected error, error must be inherit by FormatException"
                ),
                std::string("")
            );
            return;
        }
        ASSERT_EQ(std::string("Exception hasn\'t been thrown"), "");
    }
};



TEST_F(TestFormat, test_default)
{
    ASSERT_EQ("one+one = 2",
              format("{1}+{1} = {0}",
                     2, "one"));
}


TEST_F(TestFormat, test_correct_1_empty)
{
    ASSERT_EQ("", format(""));
    ASSERT_EQ("", format("", "Arg1", 3, 4, true));
}


TEST_F(TestFormat, test_correct_2_without_formating)
{
    ASSERT_EQ("I am just string",
              format("I am just string"));
    ASSERT_EQ("I am just string",
              format("I am just string",
                     "Arg1", 3, 4, true));
}


TEST_F(TestFormat, test_correct_3_one_arg)
{
    ASSERT_EQ("Argument",
              format("{0}", "Argument"));
    ASSERT_EQ(" Arg ",
              format(" {0} ", "Arg"));
    ASSERT_EQ("Has text and one arg.",
              format("Has text and {0}.",
                     "one arg"));
}


TEST_F(TestFormat, test_correct_4_no_scopes_no_args)
{
    ASSERT_EQ("Some string",
              format("Some string"));
}


TEST_F(TestFormat, test_correct_5_no_scopes_some_args)
{
    ASSERT_EQ("Some string",
              format("Some string",
                     "124", 3, true));
}


TEST_F(TestFormat, test_correct_6_one_scope_one_arg_1)
{
    ASSERT_EQ("ARG0",
              format("{0}",
                     "ARG0"));
}


TEST_F(TestFormat, test_correct_7_one_scope_one_arg_2)
{
    ASSERT_EQ("Some text and ARG0 and another text",
              format("Some text and {0} and another text",
                     "ARG0"));
}


TEST_F(TestFormat, test_correct_8_reverse_1)
{
    ASSERT_EQ("Arg3 Arg2 Arg1 Arg0",
              format("{3} {2} {1} {0}",
                     "Arg0", "Arg1", "Arg2", "Arg3"));
}

TEST_F(TestFormat, test_correct_9_reverse_2)
{
    ASSERT_EQ("Arg0 Arg3 Arg2 Arg1",
              format("{0} {3} {2} {1}",
                     "Arg0", "Arg1", "Arg2", "Arg3"));
}


TEST_F(TestFormat, test_correct_10_repeat_1)
{
    ASSERT_EQ("Arg0 or not Arg1 or Arg1 or not Arg0",
              format("{0} or not {1} or {1} or not {0}",
                     "Arg0", "Arg1"));
}


TEST_F(TestFormat, test_correct_11_repeat_2_and_without_separators)
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


TEST_F(TestFormat, test_correct_12_repeat_3)
{
    ASSERT_EQ("Its a string with missed symbol s.",
              format("It{2} a {2}tring with mi{2}{2}ed {2}ymbol {2}.",
                     2, 3, 's', "a"));
}


TEST_F(TestFormat, test_correct_13)
{
    ASSERT_EQ("234 + 12 + 234 == 480",
              format("{0} + {1} + {0} == {2}",
                     "234", 12, 480));
}


TEST_F(TestFormat, test_bad_1_one_scope_without_args)
{
    bad_format<ArgsAmountFormatException>(
        "Amount of args differs: 1 != 0",
        "Some string with {0}"
    );
}


TEST_F(TestFormat, test_bad_2_two_scopes_without_args)
{
    bad_format<ArgsAmountFormatException>(
        "Amount of args differs: 2 != 0",
        "Some string with {1} and with {0}"
    );
}


TEST_F(TestFormat, test_bad_3_more_scopes_than_args_1)
{
    bad_format<ArgsAmountFormatException>(
        "Amount of args differs: 2 != 1",
        "Qwerty {1} {0} lala",
        "I am only one"
    );
}


TEST_F(TestFormat, test_bad_4_more_scopes_than_args_2)
{
    bad_format<ArgsAmountFormatException>(
        "Amount of args differs: 11 != 5",
        "{10}",
        "Arg0", "Arg1", "Arg2", 3, 4
    );
}


TEST_F(TestFormat, test_bad_scopes_1)
{
    bad_format<ScopeFormatException>(
        "Scope error in position: 0",
        "}"
    );
    bad_format<ScopeFormatException>(
        "Scope error in position: 0",
        "{ ery", 2, 1
    );
    bad_format<ScopeFormatException>(
        "Scope error in position: 0",
        "}"
    );
    bad_format<ScopeFormatException>(
        "Scope error in position: 0",
        "{0", "arg", 0, 1, 2
    );
    bad_format<ScopeFormatException>(
        "Scope error in position: 4",
        "rdh }0 hr"
    );
    bad_format<ScopeFormatException>(
        "Scope error in position: 0",
        "{0 rh", 6
    );
    bad_format<ScopeFormatException>(
        "Scope error in position: 5",
        "wet 0}"
    );
}


TEST_F(TestFormat, test_bad_scopes_2)
{
    bad_format<ArgLexFormatException>(
        "Lex error of argument in: \"\"",
        "{}0", "arg", 0, 1, 2
    );
    bad_format<ScopeFormatException>(
        "Scope error in position: 0",
        "}0{"
    );
    bad_format<ArgLexFormatException>(
        "Lex error of argument in: \"\"",
        "0{}", "Arg"
    );
    bad_format<ScopeFormatException>(
        "Scope error in position: 7",
        "rjst {0{"
    );
    bad_format<ScopeFormatException>(
        "Scope error in position: 7",
        "reherj }0}  drh"
    );
}


TEST_F(TestFormat, test_bad_scopes_3)
{
    bad_format<ScopeFormatException>(
        "Scope error in position: 3",
        "{0}{", "Arg"
    );
    bad_format<ScopeFormatException>(
        "Scope error in position: 3",
        "}{0}", "Arg"
    );
    bad_format<ScopeFormatException>(
        "Scope error in position: 13",
        "Some text} {0} haha", false
    );
}


TEST_F(TestFormat, test_bad_scopes_4_inside_other)
{
    bad_format<ScopeFormatException>(
        "Scope error in position: 2",
        "{1{0}}",
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
    );
}


TEST_F(TestFormat, test_bad_arg_lex_0)
{
    bad_format<ArgLexFormatException>(
        "Lex error of argument in: \"\"",
        "{}", 2, 4
    );
}


TEST_F(TestFormat, test_bad_arg_lex_1)
{
    bad_format<ArgLexFormatException>(
        "Lex error of argument in: \"a\"",
        "{a}", 2, 3
    );
    bad_format<ArgLexFormatException>(
        "Lex error of argument in: \"-1\"",
        "Haha, {0} and {-1}",
        "Arg-1", "Arg0"
    );
}


TEST_F(TestFormat, test_bad_arg_lex_2)
{
    bad_format<ArgLexFormatException>(
        "Lex error of argument in: \"18446744073709551616\"",
        "{18446744073709551616}",
        "Arg", 2, 3
    );
}


TEST_F(TestFormat, test_bad_arg_lex_3)
{
    bad_format<ArgLexFormatException>(
        "Lex error of argument in: \"1sert\"",
        "Hahaah {0} {1sert} {1} ahaha",
        "Arg", 2, 3
    );
}


TEST_F(TestFormat, test_bad_arg_lex_4)
{
    bad_format<ArgLexFormatException>(
        "Lex error of argument in: \"re0\"",
        "w rgerg {0} {re0} {1} ahaha",
        2, 3, "Argument"
    );
}


TEST_F(TestFormat, test_bad_not_enough_args)
{
    bad_format<ArgsAmountFormatException>(
        "Amount of args differs: 5 != 3",
        "Exist: {0} and {1} and {2}, but haven\'t got {3} and {4}",
        0, 1, 2
    );
}


int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
