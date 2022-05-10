#ifndef MSU_CPP_SPRING_2022_MY_VECTOR_H
#define MSU_CPP_SPRING_2022_MY_VECTOR_H

#include <algorithm>

#include "my_allocator.hpp"


template<typename T, typename AllocT = Allocator<T>>
class Vector
{
public:
    using size_type = size_t;
    using value_type = T;
    using reference = T &;
    using allocator_type = AllocT;
private:


};


#endif //MSU_CPP_SPRING_2022_MY_VECTOR_H
