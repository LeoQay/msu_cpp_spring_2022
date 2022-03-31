#include <gtest/gtest.h>

#include <cstring>

#include "Allocator.hpp"


class TestAllocator : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }
    void TearDown() override
    {

    }
};

TEST_F(TestAllocator, test_init_delete)
{
    Allocator obj;
}

TEST_F(TestAllocator, test_make_allocator)
{
    Allocator obj;
    obj.makeAllocator(100);
}

TEST_F(TestAllocator, test_remake_allocator)
{
    Allocator obj;
    obj.makeAllocator(100);
    obj.makeAllocator(1000);
}


TEST_F(TestAllocator, test_alloc)
{
    Allocator obj;
    obj.makeAllocator(100);
    char * block = obj.alloc(10);
    ASSERT_TRUE(block != nullptr);
}

TEST_F(TestAllocator, test_alloc_before_make)
{
    Allocator obj;
    char * block = obj.alloc(1);
    ASSERT_TRUE(block == nullptr);
}

TEST_F(TestAllocator, test_alloc_zero_size)
{
    Allocator obj;
    char * block = obj.alloc(0);
    ASSERT_TRUE(block == nullptr);

    obj.makeAllocator(1000);
    block = obj.alloc(0);
    ASSERT_TRUE(block == nullptr);
}

TEST_F(TestAllocator, test_alloc_range_max)
{
    Allocator obj;
    obj.makeAllocator(100);
    char * block = obj.alloc(100);
    ASSERT_TRUE(block != nullptr);
}

TEST_F(TestAllocator, test_alloc_out_range)
{
    Allocator obj;
    obj.makeAllocator(100);
    char * block = obj.alloc(101);
    ASSERT_TRUE(block == nullptr);
    block = obj.alloc(1000);
    ASSERT_TRUE(block == nullptr);
    block = obj.alloc(87);
    ASSERT_TRUE(block != nullptr);
}

TEST_F(TestAllocator, test_alloc_many_little_sizes)
{
    Allocator obj;
    obj.makeAllocator(100);

    char * previous, * block = nullptr;

    for (int i = 0; i < 100; i++)
    {
        previous = block;
        block = obj.alloc(1);

        ASSERT_TRUE(block != nullptr);

        if (i > 0)
        {
            ASSERT_TRUE(block - previous == 1);
        }
    }
}

TEST_F(TestAllocator, test_saving_block_content)
{
    Allocator obj;
    obj.makeAllocator(100);

    char * block = obj.alloc(50);
    ASSERT_TRUE(block != nullptr);

    strcpy(block, "Haha, block activity testing!\n");
    ASSERT_STREQ("Haha, block activity testing!\n", block);

    char * block2 = obj.alloc(50);
    ASSERT_STREQ("Haha, block activity testing!\n", block);

    memset(block2, 0, 50);
}

TEST_F(TestAllocator, test_reset)
{
    Allocator obj;
    obj.makeAllocator(100);
    char * block = obj.alloc(50);
    ASSERT_TRUE(block != nullptr);
    memset(block, 0, 50);
    obj.reset();
    block = obj.alloc(75);
    ASSERT_TRUE(block != nullptr);
}

TEST_F(TestAllocator, test_hard)
{
    Allocator obj;
    obj.makeAllocator(1000);
    char * block = obj.alloc(50);
    ASSERT_TRUE(block != nullptr);
    memset(block, 0, 50);
    block = obj.alloc(950);
    ASSERT_TRUE(block != nullptr);
    obj.makeAllocator(10000);
    for (int i = 0; i < 10000; i += 100)
    {
        block = obj.alloc(100);
        ASSERT_TRUE(block != nullptr);
    }
    obj.reset();
    for (int i = 0; i < 10000; i += 100)
    {
        block = obj.alloc(100);
        ASSERT_TRUE(block != nullptr);
    }
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}