#include <gtest/gtest.h>

#include "matrix.hpp"


class TestMatrix : public ::testing::Test {};


TEST_F(TestMatrix, test_simple)
{

}


int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
