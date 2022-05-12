#ifndef MSU_CPP_SPRING_2022_MY_VECTOR_H
#define MSU_CPP_SPRING_2022_MY_VECTOR_H

#include <stdexcept>
#include <iterator>

#include "my_allocator.hpp"
#include "my_iterator.hpp"


template<typename T, class AllocT = Allocator<T>>
class Vector
{
public:
    using size_type = size_t;
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using allocator_type = AllocT;
    using iterator = VectorIterator<T>;
    using reverse_iterator = std::reverse_iterator<VectorIterator<T>>;

    Vector();
    explicit Vector(size_type n);
    Vector(size_type n, const_reference fill);
    Vector(const Vector & other);
    Vector(const Vector && other) noexcept;

    ~Vector();

    reference operator[] (size_type i);
    const_reference operator[] (size_type i) const;

    void push_back(const_reference value);

    template<class ...ArgsT>
    void emplace_back(ArgsT ...args);

    void pop_back();

    void clear();

    [[nodiscard]] bool empty() const noexcept;
    [[nodiscard]] size_type size() const noexcept;
    [[nodiscard]] size_type capacity() const noexcept;

    iterator begin();
    iterator end();

    reverse_iterator rbegin();
    reverse_iterator rend();

    constexpr void reserve(size_type new_cap);

    constexpr void resize(size_type count);
    constexpr void resize(size_type count, const value_type & val);

private:

    void check_array() const;
    void check_index(size_type i) const;

    T * array;
    size_type current_offset;
    size_type allocated_size;

    allocator_type allocator;
};


template<typename T, class AllocT>
Vector<T, AllocT>::Vector() :
array(nullptr),
current_offset(0),
allocated_size(0),
allocator()
{}


template<typename T, class AllocT>
Vector<T, AllocT>::Vector(size_type n) :
array(nullptr),
current_offset(n),
allocated_size(n),
allocator()
{
    if (n)
    {
        array = allocator.allocate(n);
        check_array();
    }

    if (std::enable_if<true, std::is_integral<T>>::type::value)
    {
        for (size_type i = 0; i != current_offset; i++)
        {
            array[i] = 0;
        }
    }
}


template<typename T, class AllocT>
Vector<T, AllocT>::Vector(size_type n, const_reference fill) :
array(nullptr),
current_offset(n),
allocated_size(n),
allocator()
{
    if (n)
    {
        array = allocator.allocate(n);
        check_array();
    }

    for (size_type i = 0; i != n; i++)
    {
        array[i] = fill;
    }
}


template<typename T, class AllocT>
Vector<T, AllocT>::Vector(const Vector<T, AllocT> & other) :
array(nullptr),
current_offset(other.current_offset),
allocated_size(other.current_offset),
allocator(other.allocator)
{
    if (other.current_offset == 0)
    {
        allocated_size = 0;
        return;
    }

    array = allocator.allocate(current_offset);
    check_array();

    for (size_type i = 0; i != current_offset; i++)
    {
        array[i] = other.array[i];
    }
}


template<typename T, class AllocT>
Vector<T, AllocT>::Vector(const Vector<T, AllocT> && other) noexcept :
array(other.array),
current_offset(other.current_offset),
allocated_size(other.allocated_size),
allocator(other.allocator)
{
    other.array = nullptr;
    other.current_offset = 0;
    other.allocated_size = 0;
}


template<typename T, class AllocT>
Vector<T, AllocT>::~Vector()
{
    allocator.deallocate(array, allocated_size);
    array = nullptr;
    current_offset = 0;
    allocated_size = 0;
}


template<typename T, class AllocT>
void Vector<T, AllocT>::check_array() const
{
    if (!array)
    {
        throw std::bad_alloc();
    }
}


template<typename T, class AllocT>
void Vector<T, AllocT>::check_index(size_type i) const
{
    if (i >= current_offset)
    {
        throw std::runtime_error("Bad index");
    }
}


template<typename T, class AllocT>
typename Vector<T, AllocT>::reference
Vector<T, AllocT>::operator[] (size_type i)
{
    check_array();
    check_index(i);
    return array[i];
}


template<typename T, class AllocT>
typename Vector<T, AllocT>::const_reference
Vector<T, AllocT>::operator[] (size_type i) const
{
    check_array();
    check_index(i);
    return array[i];
}


template<typename T, class AllocT>
void Vector<T, AllocT>::push_back(const_reference value)
{
    if (!array)
    {
        array = allocator.allocate(1);
        check_array();
        allocated_size = 1;
    }
    else if (current_offset >= allocated_size)
    {
        auto new_size = allocated_size << 1;
        auto new_array = allocator.allocate(new_size);
        if (!new_array)
        {
            throw std::bad_alloc();
        }
        for (size_type i = 0; i != current_offset; i++)
        {
            new_array[i] = array[i];
        }
        allocator.deallocate(array, allocated_size);
        array = new_array;
        allocated_size = new_size;
    }

    array[current_offset] = value;
    current_offset++;
}


template<typename T, class AllocT>
template<class ...ArgsT>
void Vector<T, AllocT>::emplace_back(ArgsT ...args)
{
    push_back(T(args...));
}


template<typename T, class AllocT>
void Vector<T, AllocT>::pop_back()
{
    if (current_offset == 0)
    {
        throw std::runtime_error("Can\'t pop back empty vector");
    }

    array[current_offset - 1].~T();
    current_offset--;
}


template<typename T, class AllocT>
bool Vector<T, AllocT>::empty() const noexcept
{
    return current_offset == 0;
}


template<typename T, class AllocT>
typename Vector<T, AllocT>::size_type
Vector<T, AllocT>::size() const noexcept
{
    return current_offset;
}


template<typename T, class AllocT>
typename Vector<T, AllocT>::size_type
Vector<T, AllocT>::capacity() const noexcept
{
    return allocated_size;
}


template<typename T, class AllocT>
void Vector<T, AllocT>::clear()
{
    this->~Vector<T, AllocT>();
}


template<typename T, class AllocT>
typename Vector<T, AllocT>::iterator
Vector<T, AllocT>::begin()
{
    decltype(array) ptr = nullptr;
    return iterator(array ? array : ptr + 1);
}


template<typename T, class AllocT>
typename Vector<T, AllocT>::iterator
Vector<T, AllocT>::end()
{
    decltype(array) ptr = nullptr;
    return iterator(array ? array + current_offset: ptr + 1);
}


template<typename T, class AllocT>
typename Vector<T, AllocT>::reverse_iterator
Vector<T, AllocT>::rbegin()
{
    return reverse_iterator(end());
}


template<typename T, class AllocT>
typename Vector<T, AllocT>::reverse_iterator
Vector<T, AllocT>::rend()
{
    return reverse_iterator(begin());
}


template<typename T, class AllocT>
constexpr void Vector<T, AllocT>::reserve(size_type new_cap)
{
    if (allocated_size >= new_cap)
    {
        return;
    }

    auto new_array = allocator.allocate(new_cap);
    if (!new_array)
    {
        throw std::bad_alloc();
    }
    for (size_type i = 0; i != current_offset; i++)
    {
        new_array[i] = array[i];
    }
    allocator.deallocate(array, allocated_size);
    array = new_array;
    allocated_size = new_cap;
}


template<typename T, class AllocT>
constexpr void Vector<T, AllocT>::resize(size_type count)
{
    if (count <= current_offset)
    {
        current_offset = count;
        for (size_type i = count; i != current_offset; i++)
        {
            array[i].~T();
        }
        return;
    }

    if (count > allocated_size)
    {
        auto new_array = new T[count];
        if (!new_array)
        {
            throw std::bad_alloc();
        }
        for (size_type i = 0; i != current_offset; i++)
        {
            new_array[i] = array[i];
        }

        delete [] array;
        array = new_array;
        allocated_size = count;
    }

    if (std::enable_if<true, std::is_integral<T>>::type::value)
    {
        for (size_type i = current_offset; i != count; i++)
        {
            array[i] = 0;
        }
    }

    current_offset = count;
}


template<typename T, class AllocT>
constexpr void Vector<T, AllocT>::resize(size_type count, const value_type & val)
{
    if (count <= current_offset)
    {
        current_offset = count;
        for (size_type i = count; i != current_offset; i++)
        {
            array[i].~T();
        }
        return;
    }

    if (count > allocated_size)
    {
        auto new_array = new T[count];
        if (!new_array)
        {
            throw std::bad_alloc();
        }
        for (size_type i = 0; i != current_offset; i++)
        {
            new_array[i] = array[i];
        }
        delete [] array;
        array = new_array;
        allocated_size = count;
    }

    for (size_type i = current_offset; i != count; i++)
    {
        array[i] = val;
    }

    current_offset = count;
}


#endif //MSU_CPP_SPRING_2022_MY_VECTOR_H
