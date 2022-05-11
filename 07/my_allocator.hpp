#ifndef HW_CPP_VK_MY_ALLOCATOR_HPP
#define HW_CPP_VK_MY_ALLOCATOR_HPP


#include <memory>


template<typename T>
class Allocator
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    constexpr T * allocate(std::size_t n);
    constexpr void deallocate(T * p, std::size_t n);
private:
};


template<typename T>
constexpr T * Allocator<T>::allocate(std::size_t n)
{
    if (n == 0) return nullptr;
    return new T[n];
}


template<typename T>
constexpr void Allocator<T>::deallocate(T * p, std::size_t n)
{
    delete [] p;
}


#endif //HW_CPP_VK_MY_ALLOCATOR_HPP
