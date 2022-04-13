#include <gtest/gtest.h>

#include "matrix.hpp"


class TestMatrix : public ::testing::Test {};

class TestMatrixIndexing : public TestMatrix {};

TEST_F(TestMatrix, test_init)
{
    Matrix matrix(1, 1);
}

TEST_F(TestMatrixIndexing, test_indexing_0)
{
    Matrix matrix(3, 10);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            ASSERT_EQ(matrix[i][j], 0);
        }
    }
}

TEST_F(TestMatrixIndexing, test_indexing_1)
{
    Matrix matrix(1, 1);
    matrix[0][0] = 4;
    int value = matrix[0][0];

    ASSERT_EQ(value, 4);
}

TEST_F(TestMatrixIndexing, test_indexing_2)
{
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

TEST_F(TestMatrixIndexing, test_indexing_3)
{
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


int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
