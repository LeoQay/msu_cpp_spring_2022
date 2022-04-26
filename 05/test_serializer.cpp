#include <sstream>
#include <gtest/gtest.h>


class TestSeries : public ::testing::Test {};


TEST_F(TestSeries, test_1)
{

}


int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
