#include <cstring>
#include <gtest/gtest.h>

#include "allocator.hpp"


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
    ASSERT_NE(block, nullptr);
}

TEST_F(TestAllocator, test_alloc_before_make)
{
    Allocator obj;

    char * block = obj.alloc(1);
    ASSERT_EQ(block, nullptr);

    block = obj.alloc(0);
    ASSERT_EQ(block, nullptr);
}

TEST_F(TestAllocator, test_alloc_chain_1)
{
    Allocator obj;
    obj.makeAllocator(100);

    char * block1 = obj.alloc(20);
    ASSERT_NE(block1, nullptr);

    char * block2 = obj.alloc(2);
    ASSERT_NE( block2, nullptr);
    ASSERT_EQ(block2 - block1, 20);

    char * block3 = obj.alloc(30);
    ASSERT_NE(block3, nullptr);
    ASSERT_EQ(block3 - block2, 2);

    char * block4 = obj.alloc(48);
    ASSERT_NE(block4, nullptr);
    ASSERT_EQ(block4 - block3, 30);

    char * block5 = obj.alloc(1);
    ASSERT_EQ(block5, nullptr);

    obj.reset();

    char * block6 = obj.alloc(100);
    ASSERT_NE(block6, nullptr);

    char * block7 = obj.alloc(1);
    ASSERT_EQ(block7, nullptr);
}

TEST_F(TestAllocator, test_edge_case_1)
{
    Allocator obj;
    obj.makeAllocator(1);

    char * block = obj.alloc(1);
    ASSERT_NE(block, nullptr);

    block = obj.alloc(1);
    ASSERT_EQ(block, nullptr);
}

TEST_F(TestAllocator, test_edge_case_2)
{
    Allocator obj;
    obj.makeAllocator(50);

    char * block = obj.alloc(20);
    ASSERT_NE(block, nullptr);

    block = obj.alloc(30);
    ASSERT_NE(block, nullptr);

    block = obj.alloc(1);
    ASSERT_EQ(block, nullptr);

    obj.reset();

    block = obj.alloc(50);
    ASSERT_NE(block, nullptr);

    block = obj.alloc(1);
    ASSERT_EQ(block, nullptr);
}

TEST_F(TestAllocator, test_edge_case_3)
{
    Allocator obj;
    obj.makeAllocator(25);

    char * block = obj.alloc(13);
    ASSERT_NE(block, nullptr);

    block = obj.alloc(13);
    ASSERT_EQ(block, nullptr);

    block = obj.alloc(12);
    ASSERT_NE(block, nullptr);
}

TEST_F(TestAllocator, test_alloc_zero_size)
{
    Allocator obj;
    char * block = obj.alloc(0);
    ASSERT_EQ(block, nullptr);

    obj.makeAllocator(1000);
    block = obj.alloc(0);
    ASSERT_EQ(block, nullptr);
}

TEST_F(TestAllocator, test_alloc_range_max)
{
    Allocator obj;
    obj.makeAllocator(100);

    char * block = obj.alloc(100);
    ASSERT_NE(block, nullptr);
}

TEST_F(TestAllocator, test_alloc_out_range)
{
    Allocator obj;
    obj.makeAllocator(100);

    char * block = obj.alloc(101);
    ASSERT_EQ(block, nullptr);

    block = obj.alloc(1000);
    ASSERT_EQ(block, nullptr);

    block = obj.alloc(100);
    ASSERT_NE(block, nullptr);
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

        ASSERT_NE(block, nullptr);

        if (i > 0)
        {
            ASSERT_EQ(block - previous, 1);
        }
    }
}

TEST_F(TestAllocator, test_saving_block_content)
{
    Allocator obj;
    obj.makeAllocator(100);

    char * block = obj.alloc(50);
    ASSERT_NE(block, nullptr);

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
    ASSERT_NE(block, nullptr);

    block = obj.alloc(75);
    ASSERT_EQ(block, nullptr);

    obj.reset();

    block = obj.alloc(75);
    ASSERT_NE(block, nullptr);

    obj.reset();

    block = obj.alloc(110);
    ASSERT_EQ(block, nullptr);
}

TEST_F(TestAllocator, test_just_test)
{
    Allocator obj;
    obj.makeAllocator(1000);
    char * block = obj.alloc(50);
    ASSERT_NE(block, nullptr);
    memset(block, 0, 50);
    block = obj.alloc(950);
    ASSERT_NE(block, nullptr);
    obj.makeAllocator(10000);
    for (int i = 0; i < 10000; i += 100)
    {
        block = obj.alloc(100);
        ASSERT_NE(block, nullptr);
    }
    obj.reset();
    for (int i = 0; i < 10000; i += 100)
    {
        block = obj.alloc(100);
        ASSERT_NE(block, nullptr);
    }
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}