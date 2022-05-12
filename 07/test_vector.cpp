#include <gtest/gtest.h>

#include "my_vector.hpp"


class TestMyVector : public ::testing::Test {};
class TestMyVectorBase : public TestMyVector {};
class TestMyVectorResize : public TestMyVector {};


TEST_F(TestMyVectorBase, test_base_1)
{
    Vector<int> vector;
    ASSERT_EQ(vector.size(), 0);
}

TEST_F(TestMyVectorBase, test_base_2)
{
    Vector<int> vector(10);
    ASSERT_EQ(vector.size(), 10);
}

TEST_F(TestMyVectorBase, test_base_3)
{
    Vector<int> vector(100);
    ASSERT_EQ(vector.size(), 100);

    for (int i = 0; i < 100; i++)
    {
        vector[i] = i;
    }

    for (int i = 0; i < 100; i++)
    {
        ASSERT_EQ(vector[i], i);
    }
}

TEST_F(TestMyVectorBase, test_base_4)
{
    Vector<int> vector(10, 5);
    ASSERT_EQ(vector.size(), 10);
    for (auto i : vector)
    {
        ASSERT_EQ(i, 5);
    }
}


int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
