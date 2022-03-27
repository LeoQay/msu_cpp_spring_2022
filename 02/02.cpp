#include <cstring>

using namespace std;

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

void Allocator::makeAllocator(size_t maxSize)
{
    delete [] ptr;
    offset = 0;
    max_size = maxSize;
    ptr = new char[maxSize];
}

char * Allocator::alloc(size_t size)
{
    if (offset + size > max_size)
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


int main()
{
    Allocator alloc;

    alloc.makeAllocator(100);

    char * p1 = alloc.alloc(50);
    char * p2 = alloc.alloc(30);
    char * p3 = alloc.alloc(20);

    memset(p1, 0, 50);
    memset(p2, 1, 30);
    memset(p3, 2, 20);

    alloc.reset();

    alloc.makeAllocator(1000);

    char * p4 = alloc.alloc(1000);

    memset(p4, 3, 1000);

    return 0;
}
