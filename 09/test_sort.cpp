#include <gtest/gtest.h>
#include <filesystem>

#include "test_sort.hpp"
#include "two_thread_sort.hpp"


class TestSort : public ::testing::Test {};


TEST_F(TestSort, test_very_small_size)
{
    Generator::gen("file.bin", 10);

    TwoThreadSort sorter;
    sorter.sort("file.bin", "result.bin");

    ASSERT_TRUE(SortChecker::check("result.bin"));

    std::filesystem::remove("file.bin");
    std::filesystem::remove("result.bin");
}


TEST_F(TestSort, test_small_size)
{
    Generator::gen("file.bin", 1000);

    TwoThreadSort sorter;
    sorter.sort("file.bin", "result.bin");

    ASSERT_TRUE(SortChecker::check("result.bin"));

    std::filesystem::remove("file.bin");
    std::filesystem::remove("result.bin");
}


TEST_F(TestSort, test_big_size)
{
    Generator::gen("file.bin", 10000000);

    TwoThreadSort sorter;
    sorter.sort("file.bin", "result.bin");

    ASSERT_TRUE(SortChecker::check("result.bin"));

    std::filesystem::remove("file.bin");
    std::filesystem::remove("result.bin");
}


int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
