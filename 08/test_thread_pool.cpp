#include <gtest/gtest.h>

#include "thread_pool.hpp"
#include "for_tests.hpp"


class TestThreadPool : public ::testing::Test {};


TEST_F(TestThreadPool, test_1)
{
    ThreadPool pool(1);
    auto fut = pool.exec(func_1841);
    ASSERT_EQ(fut.get(), 1841);
}


TEST_F(TestThreadPool, test_2)
{
    ThreadPool pool(1);
    auto fut = pool.exec(func_sqrt, 9);
    ASSERT_EQ(fut.get(), 3);
}


TEST_F(TestThreadPool, test_3)
{
    ThreadPool pool(2);
    auto fut1 = pool.exec(func_1841);
    auto fut2 = pool.exec(func_sqrt, 16);
    ASSERT_EQ(fut2.get(), 4);
    ASSERT_EQ(fut1.get(), 1841);
}


TEST_F(TestThreadPool, test_4)
{
    ThreadPool pool(8);
    std::vector<std::future<int>> v1;
    std::vector<std::future<int>> v2;

    for (int i = 0; i < 100; i++)
    {
        v1.push_back(pool.exec(func_1841));
        v2.push_back(pool.exec(func_sqrt, 25));
    }

    for (int i = 0; i < 100; i++)
    {
        ASSERT_EQ(v1[i].get(), 1841);
        ASSERT_EQ(v2[i].get(), 5);
    }
}


TEST_F(TestThreadPool, test_5)
{
    ThreadPool pool(8);
    std::vector<std::future<std::string>> v;

    for (int i = 0; i < 100; i++)
    {
        v.push_back(pool.exec(func_str_mul_int, "a", i));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    for (int i = 0; i < 100; i++)
    {
        ASSERT_EQ(v[i].get().size(), i);
    }
}


TEST_F(TestThreadPool, test_6)
{
    ThreadPool pool(8);

    auto fut = pool.exec(timed_function, 1000);

    auto res_time = fut.get();

    ASSERT_LE(res_time, 1001000000);
}


TEST_F(TestThreadPool, test_7)
{
    ThreadPool pool(8);
    std::vector<std::future<uint64_t>> v;
    std::vector<uint64_t> tim = {1000, 20, 100, 500, 400, 250, 120, 450};

    for (int i = 0; i < 8; i++)
    {
        v.push_back(pool.exec(timed_function, tim[i]));
    }

    for (int i = 0; i < 8; i++)
    {
        auto res_time = v[i].get();
        ASSERT_LE(res_time - tim[i] * 1000000, 1000000);
    }
}



int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
