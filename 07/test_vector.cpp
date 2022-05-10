#include <gtest/gtest.h>

#include "my_vector.hpp"


class TestMyVector : public ::testing::Test {};


TEST_F(TestMyVector, test_1)
{

}


int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
