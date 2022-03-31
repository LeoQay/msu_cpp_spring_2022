#include <stdexcept>

#include "Allocator.hpp"

void Allocator::makeAllocator(size_t maxSize)
{
    delete [] ptr;
    offset = 0;
    max_size = maxSize;
    ptr = new char[maxSize];
}

char * Allocator::alloc(size_t size)
{
    if (size == 0 || offset + size > max_size)
    {
        return nullptr;
    }

    char * ret = ptr + offset;
    offset += size;
    return ret;
}

void Allocator::reset()
{
    offset = 0;
}
Allocator::~Allocator()
{
    delete [] ptr;
}
