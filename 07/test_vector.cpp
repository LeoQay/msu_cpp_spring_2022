#include <gtest/gtest.h>

#include "my_vector.hpp"


class TestMyVector : public ::testing::Test {};
class TestMyVectorBase : public TestMyVector {};
class TestMyVectorIndexAndIter : public TestMyVector {};
class TestMyVectorDynamic : public TestMyVector {};


TEST_F(TestMyVectorBase, test_base_1)
{
    Vector<int> vector;
    ASSERT_EQ(vector.size(), 0);
    ASSERT_TRUE(vector.size() <= vector.capacity());
}

TEST_F(TestMyVectorBase, test_base_2)
{
    Vector<int> vector(10);
    ASSERT_EQ(vector.size(), 10);
    ASSERT_TRUE(vector.size() <= vector.capacity());
    for (int i = 0; i < 10; i++)
    {
        ASSERT_EQ(vector[i], 0);
    }
}

TEST_F(TestMyVectorBase, test_base_3)
{
    Vector<int> vector(100);
    ASSERT_EQ(vector.size(), 100);
    ASSERT_TRUE(vector.size() <= vector.capacity());

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
    ASSERT_TRUE(vector.size() <= vector.capacity());
    for (auto i : vector)
    {
        ASSERT_EQ(i, 5);
    }
}


TEST_F(TestMyVectorBase, test_base_5)
{
    Vector<int> vector(10, 5);
    Vector<int> v2 = vector;
    ASSERT_EQ(v2.size(), 10);
    ASSERT_EQ(vector.size(), 10);
    ASSERT_TRUE(vector.size() <= vector.capacity());
    ASSERT_TRUE(v2.size() <= v2.capacity());
    for (auto i : vector)
    {
        ASSERT_EQ(i, 5);
    }
    for (auto i : v2)
    {
        ASSERT_EQ(i, 5);
    }
}


TEST_F(TestMyVectorIndexAndIter, test_i_1)
{
    Vector<int> vector;
    ASSERT_EQ(vector.begin(), vector.end());
}


TEST_F(TestMyVectorIndexAndIter, test_i_2)
{
    Vector<int> vector(1);
    auto it1 = vector.begin();
    auto it2 = vector.end();
    ASSERT_NE(it1, it2);
    ASSERT_EQ(it1 + 1, it2);
    ++it1;
    ASSERT_EQ(it1, it2);
}

TEST_F(TestMyVectorIndexAndIter, test_i_3)
{
    Vector<int> vector(3, 10);
    for (auto it = vector.begin(); it != vector.end(); it++)
    {
        ASSERT_EQ(*it, 10);
    }

    for (int & it : vector)
    {
        ASSERT_EQ(it, 10);
    }
}


TEST_F(TestMyVectorIndexAndIter, test_i_4)
{
    Vector<int> vector(10);

    auto it0 = vector.begin();
    auto it01 = it0 + 1;
    auto it05 = it0 + 5;
    auto it015 = it01 + 4;

    for (int i = 0; i < 10; i++)
    {
        vector[i] = 9 - i;
    }

    ASSERT_EQ(*it0, 9);
    ASSERT_EQ(*it01, 8);
    ASSERT_EQ(*it05, 4);
    ASSERT_EQ(*it015, 4);

    ASSERT_EQ(it01, it0 + 1);
    ASSERT_EQ(it01 - 1, it0);

    ASSERT_EQ(it05, it0 + 5);
    ASSERT_EQ(it05 - 5, it0);

    ASSERT_EQ(it05, it01 + 4);
    ASSERT_EQ(it05 - 4, it01);
}


TEST_F(TestMyVectorIndexAndIter, test_i_5)
{
    Vector<int> vector(10, 5);

    for (auto it = vector.rbegin(); it != vector.rend(); it++)
    {
        ASSERT_EQ(*it, 5);
    }
}


TEST_F(TestMyVectorIndexAndIter, test_i_6)
{
    Vector<int> vector(2);
    vector[0] = 3;
    vector[1] = 1;

    auto it1 = vector.rbegin();
    auto it2 = vector.rend();

    ASSERT_NE(it1, it2);
    ASSERT_EQ(it1 + 2, it2);
    ASSERT_EQ(it2 - 2, it1);
    ASSERT_EQ(it1 + 1, it2 - 1);

    ASSERT_EQ(*it1, 1);
    ASSERT_EQ(*(it2 - 1), 3);

    --it2;
    ++it1;
    ASSERT_EQ(it1, it2);
}


TEST_F(TestMyVectorIndexAndIter, test_i_7)
{
     Vector<int> vector(2, 2);
     auto it1 = vector.begin();
     auto it2 = vector.end();

     ASSERT_TRUE(it1 < it2);
     ASSERT_TRUE(it1 <= it2);
     ASSERT_TRUE(it1 != it2);
     ASSERT_FALSE(it1 > it2);
     ASSERT_FALSE(it1 >= it2);
     ASSERT_FALSE(it1 == it2);
}


TEST_F(TestMyVectorIndexAndIter, test_i_8)
{
    Vector<int> vector(2, 2);
    auto it1 = vector.rbegin();
    auto it2 = vector.rend();

    ASSERT_TRUE(it1 < it2);
    ASSERT_TRUE(it1 <= it2);
    ASSERT_TRUE(it1 != it2);
    ASSERT_FALSE(it1 > it2);
    ASSERT_FALSE(it1 >= it2);
    ASSERT_FALSE(it1 == it2);
}


TEST_F(TestMyVectorDynamic, test_d_1)
{
    Vector<int> vector;
    vector.push_back(1);
    ASSERT_EQ(vector.size(), 1);
    ASSERT_EQ(vector[0], 1);
}


TEST_F(TestMyVectorDynamic, test_d_2)
{
    Vector<int> vector(1, 10);
    vector.push_back(1);
    ASSERT_EQ(vector.size(), 2);
    ASSERT_EQ(vector[0], 10);
    ASSERT_EQ(vector[1], 1);
}


TEST_F(TestMyVectorDynamic, test_d_3)
{
    Vector<int> vector(2, 10);
    vector.push_back(4);
    ASSERT_EQ(vector.size(), 3);
    ASSERT_EQ(vector[0], 10);
    ASSERT_EQ(vector[2], 4);
    vector.push_back(120);
    ASSERT_EQ(vector.size(), 4);
    ASSERT_EQ(vector[0], 10);
    ASSERT_EQ(vector[1], 10);
    ASSERT_EQ(vector[2], 4);
    ASSERT_EQ(vector[3], 120);
}


TEST_F(TestMyVectorDynamic, test_d_4)
{
    Vector<int> vector;
    for (int i = 0; i < 1000; i++)
    {
        vector.push_back(i * 2 - 23);
        ASSERT_EQ(vector.size(), i + 1);
    }
    for (int i = 0; i < 1000; i++) ASSERT_EQ(vector[i], i * 2 - 23);
}


TEST_F(TestMyVectorDynamic, test_d_5)
{
    Vector<int> vector;
    ASSERT_TRUE(vector.empty());
    vector.resize(20);
    ASSERT_EQ(vector.size(), 20);
    for (int i = 0; i < 20; i++) vector[i] = i + 5;
    ASSERT_FALSE(vector.empty());
}


TEST_F(TestMyVectorDynamic, test_d_6)
{
    Vector<int> vector(10, 3);
    vector.resize(20);
    ASSERT_EQ(vector.size(), 20);
    for (int i = 0; i < 10; i++) ASSERT_EQ(vector[i], 3);
    for (int i = 10; i < 20; i++) vector[i] = 5;
    vector.resize(20);
    ASSERT_EQ(vector.size(), 20);
    for (int i = 0; i < 10; i++) ASSERT_EQ(vector[i], 3);
    for (int i = 10; i < 20; i++) ASSERT_EQ(vector[i], 5);
}


TEST_F(TestMyVectorDynamic, test_d_7)
{
    Vector<int> vector(100, 2);
    ASSERT_EQ(vector.size(), 100);
    vector.resize(20);
    ASSERT_EQ(vector.size(), 20);
}


TEST_F(TestMyVectorDynamic, test_d_8)
{
    Vector<int> vector(50, 1);

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 200; j++) vector.push_back(j + 50);
        vector.resize(50);
    }

    ASSERT_EQ(vector.size(), 50);
    for (int i = 0; i < 50; i++) ASSERT_EQ(vector[i], 1);
}


TEST_F(TestMyVectorDynamic, test_d_9)
{
    Vector<int> vector;

    vector.push_back(1);
    vector.pop_back();
    ASSERT_TRUE(vector.empty());

    vector.push_back(2);
    vector.push_back(3);
    ASSERT_EQ(vector.size(), 2);

    vector.pop_back();
    ASSERT_EQ(vector.size(), 1);

    vector.pop_back();
    ASSERT_TRUE(vector.empty());
}


TEST_F(TestMyVectorDynamic, test_d_10)
{
    Vector<int> vector(50, 1);

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 200; j++) vector.push_back(j + 50);
        for (int j = 0; j < 200; j++) vector.pop_back();
    }

    ASSERT_EQ(vector.size(), 50);
    for (int i = 0; i < 50; i++) ASSERT_EQ(vector[i], 1);
}




int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
