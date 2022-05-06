#include <gtest/gtest.h>

#include "format.hpp"


class TestFormat : public ::testing::Test
{
public:
    template<class... ArgsT>
    void good_format(const std::string & correct,
                     const std::string & to_format, const ArgsT & ...args)
    {
        std::string result;

        try {
            result = format(to_format, args...);
        }
        catch (FormatException & err)
        {
            std::string msg = err.what();
            ASSERT_EQ(msg, "No exceptions");
        }
        catch (...)
        {
            ASSERT_EQ("Exception has been thrown", "");
        }

        ASSERT_EQ(result, correct);
    }

    template<class... ArgsT>
    void bad_format(const std::string & to_format, const ArgsT & ...args)
    {
        try {
            format(to_format, args...);
        }
        catch (...)
        {
            return;
        }

        ASSERT_EQ("Exception hasn\'t been thrown", "");
    }
};


TEST_F(TestFormat, test_default)
{
    good_format("one+one = 2",
                "{1}+{1} = {0}",
                2, "one");
}


TEST_F(TestFormat, test_no_scopes_no_args)
{
    good_format("Some string", "Some string");
}


TEST_F(TestFormat, test_no_scopes_some_args)
{
    good_format("Some string",
                "Some string",
                "124", 3, true);
}


TEST_F(TestFormat, test_some_scopes_no_args_1)
{
    bad_format("Some string with {0}");
}


TEST_F(TestFormat, test_some_scopes_no_args_2)
{
    bad_format("Some string with {1} and with {0}");
}


TEST_F(TestFormat, test_one_scope_one_arg_1)
{
    good_format("ARG0",
                "{0}",
                "ARG0");
}


TEST_F(TestFormat, test_one_scope_one_arg_2)
{
    good_format("Some text and ARG0 and another text",
                "Some text and {0} and another text",
                "ARG0");
}


TEST_F(TestFormat, test_more_scopes_than_args_1)
{
    bad_format("Qwerty {1} {0} lala",
               "I am only one");
}


TEST_F(TestFormat, test_more_scopes_than_args_2)
{
    bad_format("{10}",
               "Arg0", "Arg1", "Arg2", 3, 4);
}


TEST_F(TestFormat, test_reverse_1)
{
    good_format("Arg3 Arg2 Arg1 Arg0",
                "{3} {2} {1} {0}",
                "Arg0", "Arg1", "Arg2", "Arg3");
}

TEST_F(TestFormat, test_reverse_2)
{
    good_format("Arg0 Arg3 Arg2 Arg1",
                "{0} {3} {2} {1}",
                "Arg0", "Arg1", "Arg2", "Arg3");
}


TEST_F(TestFormat, test_bad_scopes_1)
{
    bad_format("}");
    bad_format("{ ery", 2, 1);
    bad_format("}");
    bad_format("{0", "arg", 0, 1, 2);
    bad_format("rdh }0 hr");
    bad_format("{0 rh", 6);
    bad_format("wet 0}");
}


TEST_F(TestFormat, test_bad_scopes_2)
{
    bad_format("{}0", "arg", 0, 1, 2);
    bad_format("}0{");
    bad_format("0{}", "Arg");
    bad_format("rjst {0{");
    bad_format("reherj }0}  drh");
}


TEST_F(TestFormat, test_bad_arg_lex)
{
    bad_format("{a}", 2, 3);
    bad_format("Haha, {0} and {-1}",
               "Arg-1", "Arg0");
}


TEST_F(TestFormat, test_repeat_1)
{
    good_format("Arg0 or not Arg1 or Arg1 or not Arg0",
                "{0} or not {1} or {1} or not {0}",
                "Arg0", "Arg1");
}


TEST_F(TestFormat, test_repeat_2_and_only_scopes)
{
    good_format("ArgumentArgumentArgumentArgument",
                "{0}{0}{0}{0}",
                "Argument", 2, true, 3);

    good_format("2222",
                "{1}{1}{1}{1}",
                "Argument", 2, true, 3);

    good_format("3333",
                "{3}{3}{3}{3}",
                "Argument", 2, true, 3);
}


int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
