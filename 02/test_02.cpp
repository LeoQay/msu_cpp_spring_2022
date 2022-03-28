#include <gtest/gtest.h>
#include <iostream>
#include <cstring>
#include <vector>

#include "Allocator.h"


void test_init_delete()
{
    try {
        Allocator obj;
        obj.makeAllocator(10);
    }
    catch (...)
    {
        ASSERT_TRUE(false);
    }
}

void test_remake_allocator()
{
    try {
        Allocator obj;
        obj.makeAllocator(100);
        obj.makeAllocator(1000);
    }
    catch (...)
    {
        ASSERT_TRUE(false);
    }
}

void test_allocate()
{
    try {
        Allocator obj;
        obj.makeAllocator(100);
        char * block = obj.alloc(10);
        ASSERT_TRUE(block != nullptr);
    }
    catch (...)
    {
        ASSERT_TRUE(false);
    }
}

void test_allocate_range_max()
{
    try {
        Allocator obj;
        obj.makeAllocator(100);
        char * block = obj.alloc(100);
        ASSERT_TRUE(block != nullptr);
    }
    catch (...)
    {
        ASSERT_TRUE(false);
    }
}

void test_allocate_more_size()
{
    try {
        Allocator obj;
        obj.makeAllocator(100);
        char * block = obj.alloc(101);
        ASSERT_TRUE(block == nullptr);
    }
    catch (...)
    {
        ASSERT_TRUE(false);
    }
}

void test_allocate_many_times()
{
    try {
        Allocator obj;
        obj.makeAllocator(100);

        for (int i = 0; i < 100; i++)
        {
            char * block = obj.alloc(1);
            ASSERT_TRUE(block != nullptr);
        }
    }
    catch (...)
    {
        ASSERT_TRUE(false);
    }
}

void test_block_activity()
{
    try {
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
    catch (...)
    {
        ASSERT_TRUE(false);
    }
}

void test_reset()
{
    try {
        Allocator obj;
        obj.makeAllocator(100);
        char * block = obj.alloc(50);
        ASSERT_TRUE(block != nullptr);
        memset(block, 0, 50);
        obj.reset();
        block = obj.alloc(75);
        ASSERT_TRUE(block != nullptr);
    }
    catch (...)
    {
        ASSERT_TRUE(false);
    }
}

void test_hard()
{
    try {
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
    catch (...)
    {
        ASSERT_TRUE(false);
    }
}


int main()
{
    std::vector<void (*) ()> tests;

    tests.push_back(test_init_delete);
    tests.push_back(test_remake_allocator);
    tests.push_back(test_allocate);
    tests.push_back(test_allocate_range_max);
    tests.push_back(test_allocate_more_size);
    tests.push_back(test_allocate_many_times);
    tests.push_back(test_block_activity);

    for (int i = 0; i < tests.size(); i++)
    {
        tests[i]();
        std::cout << "Test " << i << " done" << std::endl;
    }

    std::cout << "Success\n";

    return 0;
}