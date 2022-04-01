#include <cstring>
#include "allocator.hpp"

using namespace std;

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
