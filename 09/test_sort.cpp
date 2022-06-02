#include <gtest/gtest.h>
#include <filesystem>

#include "test_sort.hpp"
#include "two_thread_sort.hpp"


class TestSort : public ::testing::Test {};


TEST_F(TestSort, test_very_simple)
{
    Generator::gen("file.bin", 10000000);

    TwoThreadSort sorter;
    sorter.sort("file.bin", "result.bin");

    std::cout << SortChecker::check("result.bin");

    std::filesystem::remove("file.bin");
    std::filesystem::remove("result.bin");
}


int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
