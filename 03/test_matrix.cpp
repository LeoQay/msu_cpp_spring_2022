#include <sstream>
#include <string>
#include <gtest/gtest.h>


#include "matrix.hpp"


class TestMatrix : public ::testing::Test
{
public:
    static void check_shape(const Matrix & matrix, size_t rows, size_t columns);
    static void fill(Matrix & matrix, int32_t value);
};

void TestMatrix::check_shape(const Matrix & matrix, size_t rows, size_t columns)
{
    ASSERT_EQ(matrix.get_rows(), rows);
    ASSERT_EQ(matrix.get_columns(), columns);
}

void TestMatrix::fill(Matrix & matrix, int32_t value)
{
    for (size_t i = 0; i != matrix.get_rows(); i++)
    {
        for (size_t j = 0; j != matrix.get_columns(); j++)
        {
            matrix[i][j] = value;
        }
    }
}

class TestMatrixBase : public TestMatrix {};

class TestMatrixIndexing : public TestMatrix {};

class TestMatrixCopy : public TestMatrix {};

class TestMatrixAdd : public TestMatrix {};

class TestMatrixMul : public TestMatrix {};

class TestMatrixEQ : public TestMatrix {};

class TestMatrixNE : public TestMatrix {};

class TestMatrixPrint : public TestMatrix {};


TEST_F(TestMatrixBase, test_init)
{
    Matrix matrix(1, 1);
    check_shape(matrix, 1, 1);
}

TEST_F(TestMatrixBase, test_init_zero_1)
{
    try {
        Matrix matrix1(0, 10);
    }
    catch (std::range_error &)
    {
        return;
    }
    ASSERT_TRUE(false);
}

TEST_F(TestMatrixBase, test_init_zero_2)
{
    try {
        Matrix matrix2(2, 0);
    }
    catch (std::range_error &)
    {
        return;
    }
    ASSERT_TRUE(false);
}

TEST_F(TestMatrixIndexing, test_indexing_0)
{
    Matrix matrix(3, 10);
    check_shape(matrix, 3, 10);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            ASSERT_EQ(matrix[i][j], 0);
            check_shape(matrix, 3, 10);
        }
    }
}

TEST_F(TestMatrixIndexing, test_indexing_1)
{
    Matrix matrix(1, 1);
    check_shape(matrix, 1, 1);

    matrix[0][0] = 4;
    check_shape(matrix, 1, 1);

    int value = matrix[0][0];
    check_shape(matrix, 1, 1);

    ASSERT_EQ(value, 4);
}

TEST_F(TestMatrixIndexing, test_indexing_2)
{
    Matrix matrix(10, 10);
    check_shape(matrix, 10, 10);

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            matrix[i][j] = i + j;
            check_shape(matrix, 10, 10);
        }
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            ASSERT_EQ(matrix[i][j], i + j);
            check_shape(matrix, 10, 10);
        }
    }
}

TEST_F(TestMatrixIndexing, test_indexing_3)
{
    Matrix matrix(1000, 20);
    check_shape(matrix, 1000, 20);

    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            matrix[i][j] = i + j;
            check_shape(matrix, 1000, 20);
        }
    }

    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            ASSERT_EQ(matrix[i][j], i + j);
            check_shape(matrix, 1000,20);
        }
    }
}

TEST_F(TestMatrixIndexing, test_indexing_wrong_params_1)
{
    Matrix matrix(10, 20);
    check_shape(matrix, 10, 20);

    try {
        matrix[10][0];
    }
    catch (std::out_of_range &)
    {
        return;
    }

    ASSERT_TRUE(false);
}

TEST_F(TestMatrixIndexing, test_indexing_wrong_params_2)
{
    Matrix matrix(12, 2);
    check_shape(matrix, 12, 2);

    try {
        matrix[11][2];
    }
    catch (std::out_of_range &)
    {
        return;
    }

    ASSERT_TRUE(false);
}

TEST_F(TestMatrixCopy, test_copy_1)
{
    Matrix matrix1(1, 1);
    check_shape(matrix1, 1, 1);

    matrix1[0][0] = 123;
    check_shape(matrix1, 1, 1);

    Matrix matrix2(matrix1);
    check_shape(matrix2, 1, 1);
    check_shape(matrix1, 1, 1);

    ASSERT_EQ(matrix1[0][0], 123);
    ASSERT_EQ(matrix2[0][0], 123);

    check_shape(matrix2, 1, 1);
    check_shape(matrix1, 1, 1);
}

TEST_F(TestMatrixCopy, test_copy_2)
{
    Matrix matrix1(1, 1);
    check_shape(matrix1, 1, 1);

    matrix1[0][0] = -12;
    check_shape(matrix1, 1, 1);

    Matrix matrix2 = matrix1;
    check_shape(matrix2, 1, 1);
    check_shape(matrix1, 1, 1);

    ASSERT_EQ(matrix1[0][0], -12);
    ASSERT_EQ(matrix2[0][0], -12);

    check_shape(matrix2, 1, 1);
    check_shape(matrix1, 1, 1);
}

TEST_F(TestMatrixCopy, test_copy_3)
{
    Matrix matrix1 = Matrix(2, 10);
    check_shape(matrix1, 2, 10);
    fill(matrix1, 23);

    Matrix matrix2 = matrix1;
    check_shape(matrix2, 2, 10);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            ASSERT_EQ(matrix1[i][j], 23);
            ASSERT_EQ(matrix2[i][j], 23);
        }
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            matrix1[i][j] = 10;
            ASSERT_EQ(matrix2[i][j], 23);
        }
    }
}

TEST_F(TestMatrixCopy, test_copy_4)
{
    Matrix matrix(3, 4);
    check_shape(matrix, 3, 4);
    fill(matrix, 4);
    matrix = matrix;
    check_shape(matrix, 3, 4);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ASSERT_EQ(matrix[i][j], 4);
        }
    }
}

TEST_F(TestMatrixAdd, test_add_1)
{
    Matrix matrix1(1, 1);
    matrix1[0][0] = 23;
    Matrix matrix2(1, 1);
    matrix2[0][0] = -22;
    matrix2 = matrix2 + matrix1;

    ASSERT_EQ(matrix1[0][0], 23);
    ASSERT_EQ(matrix2[0][0], 1);
}

TEST_F(TestMatrixAdd, test_add_2)
{
    Matrix matrix1(10, 4);
    fill(matrix1, 3);

    Matrix matrix2(10, 4);
    fill(matrix2, 5);

    matrix2 = matrix1 + matrix2;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ASSERT_EQ(matrix2[i][j], 8);
            ASSERT_EQ(matrix1[i][j], 3);
        }
    }
}

TEST_F(TestMatrixAdd, test_add_3)
{
    Matrix matrix1 = Matrix(2, 3);
    fill(matrix1, 2);

    Matrix matrix2 = matrix1 + matrix1;
    check_shape(matrix2, matrix1.get_rows(), matrix1.get_columns());

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            ASSERT_EQ(matrix1[i][j], 2);
            ASSERT_EQ(matrix2[i][j], 4);
        }
    }
}

TEST_F(TestMatrixAdd, test_add_diff_shapes_1)
{
    Matrix matrix1(4, 5);
    Matrix matrix2(4, 4);

    try {
        Matrix result = matrix1 + matrix2;
    }
    catch (std::range_error &)
    {
        return;
    }

    ASSERT_TRUE(false);
}

TEST_F(TestMatrixAdd, test_add_diff_shapes_2)
{
    Matrix matrix1(2, 4);
    Matrix matrix2(3, 4);

    try {
        Matrix result = matrix1 + matrix2;
    }
    catch (std::range_error &)
    {
        return;
    }

    ASSERT_TRUE(false);
}

TEST_F(TestMatrixAdd, test_add_inplace_1)
{
    Matrix matrix1(1, 1);
    matrix1[0][0] = 23;
    Matrix matrix2(1, 1);
    matrix2[0][0] = -22;
    matrix2 += matrix1;

    ASSERT_EQ(matrix1[0][0], 23);
    ASSERT_EQ(matrix2[0][0], 1);
}

TEST_F(TestMatrixAdd, test_add_inplace_2)
{
    Matrix matrix1(10, 4);
    fill(matrix1, 3);

    Matrix matrix2(10, 4);
    fill(matrix2, 5);

    matrix2 += matrix1;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ASSERT_EQ(matrix2[i][j], 8);
            ASSERT_EQ(matrix1[i][j], 3);
        }
    }
}

TEST_F(TestMatrixAdd, test_add_inplace_diff_shapes_1)
{
    Matrix matrix1(4, 5);
    Matrix matrix2(4, 4);

    try {
        matrix1 += matrix2;
    }
    catch (std::range_error &)
    {
        return;
    }

    ASSERT_TRUE(false);
}

TEST_F(TestMatrixAdd, test_add_inplace_diff_shapes_2)
{
    Matrix matrix1(2, 4);
    Matrix matrix2(3, 4);

    try {
        matrix1 += matrix2;
    }
    catch (std::range_error &)
    {
        return;
    }

    ASSERT_TRUE(false);
}

TEST_F(TestMatrixMul, test_mul_1)
{
    Matrix matrix(2, 3);
    fill(matrix, 3);
    matrix = matrix * 2;
    check_shape(matrix, 2, 3);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            ASSERT_EQ(matrix[i][j], 6);
        }
    }
}

TEST_F(TestMatrixMul, test_mul_2)
{
    Matrix matrix = Matrix(3, 4);
    fill(matrix, 12);
    Matrix result = matrix * 6;
    check_shape(result, 3, 4);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ASSERT_EQ(matrix[i][j], 12);
            ASSERT_EQ(result[i][j], 72);
        }
    }
}

TEST_F(TestMatrixMul, test_mul_3)
{
    Matrix matrix(5, 2);
    fill(matrix, -4);
    matrix = matrix * -1;
    check_shape(matrix, 5, 2);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            ASSERT_EQ(matrix[i][j], 4);
        }
    }
}

TEST_F(TestMatrixMul, test_mul_inplace_1)
{
    Matrix matrix(1, 1);
    matrix[0][0] = 12;
    matrix *= -1;

    ASSERT_EQ(matrix[0][0], -12);
}

TEST_F(TestMatrixMul, test_mul_inplace_2)
{
    Matrix matrix(3, 5);
    fill(matrix, 12);
    matrix *= 10;
    check_shape(matrix, 3, 5);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            ASSERT_EQ(matrix[i][j], 120);
        }
    }
}

TEST_F(TestMatrixEQ, test_eq_1)
{
    Matrix matrix1(1, 1);
    matrix1[0][0] = 2;
    Matrix matrix2(1, 1);
    matrix2[0][0] = 2;
    ASSERT_TRUE(matrix1 == matrix2);
    matrix1[0][0] = 3;
    ASSERT_FALSE(matrix1 == matrix2);
}

TEST_F(TestMatrixEQ, test_eq_2)
{
    Matrix matrix(2, 3);
    fill(matrix, 4);
    ASSERT_TRUE(matrix == matrix);
}

TEST_F(TestMatrixEQ, test_eq_3)
{
    Matrix matrix1(3, 4);
    fill(matrix1, 2);
    Matrix matrix2(3, 4);
    fill(matrix2, 2);
    ASSERT_TRUE(matrix1 == matrix2);
    matrix2[2][3] = 3;
    ASSERT_FALSE(matrix1 == matrix2);
    matrix2[2][3] = 2;
    ASSERT_TRUE(matrix1 == matrix2);
    matrix1[0][0] = 1;
    ASSERT_FALSE(matrix1 == matrix2);
}

TEST_F(TestMatrixEQ, test_eq_diff_shapes)
{
    Matrix matrix1(1, 1), matrix2(1, 2);
    fill(matrix1, 1);
    fill(matrix2, 1);
    ASSERT_FALSE(matrix1 == matrix2);
}

TEST_F(TestMatrixNE, test_ne_1)
{
    Matrix matrix1(1, 1);
    matrix1[0][0] = 2;
    Matrix matrix2(1, 1);
    matrix2[0][0] = 2;
    ASSERT_FALSE(matrix1 != matrix2);
    matrix1[0][0] = 3;
    ASSERT_TRUE(matrix1 != matrix2);
}

TEST_F(TestMatrixNE, test_ne_2)
{
    Matrix matrix(2, 3);
    fill(matrix, 4);
    ASSERT_FALSE(matrix != matrix);
}

TEST_F(TestMatrixNE, test_ne_3)
{
    Matrix matrix1(3, 4);
    fill(matrix1, 2);
    Matrix matrix2(3, 4);
    fill(matrix2, 2);
    ASSERT_FALSE(matrix1 != matrix2);
    matrix2[2][3] = 3;
    ASSERT_TRUE(matrix1 != matrix2);
    matrix2[2][3] = 2;
    ASSERT_FALSE(matrix1 != matrix2);
    matrix1[0][0] = 1;
    ASSERT_TRUE(matrix1 != matrix2);
}

TEST_F(TestMatrixNE, test_ne_diff_shapes)
{
    Matrix matrix1(1, 1), matrix2(1, 2);
    fill(matrix1, 1);
    fill(matrix2, 1);
    ASSERT_TRUE(matrix1 != matrix2);
}

TEST_F(TestMatrixPrint, test_print_1)
{
    Matrix matrix(1, 1);
    fill(matrix, 2);

    std::stringstream stream;
    stream << matrix;
    std::string str = stream.str();
    ASSERT_EQ(str, "2\n");
}

TEST_F(TestMatrixPrint, test_print_2)
{
    Matrix matrix(2, 3);
    fill(matrix, 12);
    matrix[1][2] = 5;
    matrix[0][1] = 9;

    std::stringstream stream;
    stream << matrix;
    std::string str = stream.str();
    ASSERT_EQ(str, "12\t9\t12\n12\t12\t5\n");
}


int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
