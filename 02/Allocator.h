#ifndef INC_02_ALLOCATOR_H
#define INC_02_ALLOCATOR_H

#include <cstring>

class Allocator
{
public:
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    ~Allocator();

private:
    char * ptr = nullptr;
    size_t offset = 0;
    size_t max_size = 0;
};

#endif //INC_02_ALLOCATOR_H
