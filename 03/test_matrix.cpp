#include <gtest/gtest.h>

#include "matrix.hpp"


class TestMatrix : public ::testing::Test {};


TEST_F(TestMatrix, test_init)
{
    Matrix matrix(1, 1);
}

TEST_F(TestMatrix, test_indexing_1)
{
    try {
        Matrix matrix(1, 1);
        matrix[0][0] = 4;
        ASSERT_EQ(matrix[0][0], 4);
    }
    catch (...)
    {
        ASSERT_TRUE(false);
    }
}

TEST_F(TestMatrix, test_indexing_2)
{
    try {
        Matrix matrix(10, 10);

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                matrix[i][j] = i + j;
            }
        }

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                ASSERT_EQ(matrix[i][j], i + j);
            }
        }
    }
    catch (...)
    {
        ASSERT_TRUE(false);
    }
}

TEST_F(TestMatrix, test_indexing_3)
{
    try {
        Matrix matrix(1000, 20);

        for (int i = 0; i < 1000; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                matrix[i][j] = i + j;
            }
        }

        for (int i = 0; i < 1000; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                ASSERT_EQ(matrix[i][j], i + j);
            }
        }
    }
    catch (...)
    {
        ASSERT_TRUE(false);
    }
}


int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
