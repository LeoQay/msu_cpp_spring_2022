#include <gtest/gtest.h>

class TestThreadPool : public ::testing::Test {};


int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
