#ifndef HW_CPP_VK_MY_ITERATOR_HPP
#define HW_CPP_VK_MY_ITERATOR_HPP


#include <iterator>


template<typename T>
class VectorIterator : public std::iterator<std::random_access_iterator_tag, T>
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;

    explicit VectorIterator(T * ptr);

    reference operator * () const;
    pointer operator -> () const;

    reference operator[] (std::int64_t n) const;

    VectorIterator<T> & operator++ ();
    VectorIterator<T> & operator-- ();
    const VectorIterator<T> operator++ (int);
    const VectorIterator<T> operator-- (int);

    VectorIterator<T> & operator+= (std::int64_t n);
    VectorIterator<T> & operator-= (std::int64_t n);

    VectorIterator<T> operator+ (std::int64_t n) const;
    VectorIterator<T> operator- (std::int64_t n) const;

    difference_type operator- (const VectorIterator<T> & other) const;

    bool operator== (const VectorIterator<T> & other) const;
    bool operator!= (const VectorIterator<T> & other) const;
    bool operator> (const VectorIterator<T> & other) const;
    bool operator< (const VectorIterator<T> & other) const;
    bool operator>= (const VectorIterator<T> & other) const;
    bool operator<= (const VectorIterator<T> & other) const;
private:
    pointer ptr_;
};


template<typename T>
VectorIterator<T>::VectorIterator(pointer ptr) : ptr_(ptr) {}


template<typename T>
bool VectorIterator<T>::operator== (const VectorIterator<T> & other) const
{
    return ptr_ == other.ptr_;
}


template<typename T>
bool VectorIterator<T>::operator!= (const VectorIterator<T> & other) const
{
    return ptr_ != other.ptr_;
}


template<typename T>
bool VectorIterator<T>::operator> (const VectorIterator<T> & other) const
{
    return ptr_ > other.ptr_;
}


template<typename T>
bool VectorIterator<T>::operator< (const VectorIterator<T> & other) const
{
    return ptr_ < other.ptr_;
}


template<typename T>
bool VectorIterator<T>::operator>= (const VectorIterator<T> & other) const
{
    return ptr_ >= other.ptr_;
}


template<typename T>
bool VectorIterator<T>::operator<= (const VectorIterator<T> & other) const
{
    return ptr_ <= other.ptr_;
}


template<typename T>
typename VectorIterator<T>::difference_type
VectorIterator<T>::operator- (const VectorIterator<T> & other) const
{
    return ptr_ - other.ptr_;
}


template<typename T>
typename VectorIterator<T>::reference
VectorIterator<T>::operator*() const
{
    return *ptr_;
}


template<typename T>
typename VectorIterator<T>::pointer
VectorIterator<T>::operator-> () const
{
    return ptr_;
}


template<typename T>
VectorIterator<T> & VectorIterator<T>::operator++ ()
{
    ptr_++;
    return *this;
}


template<typename T>
VectorIterator<T> & VectorIterator<T>::operator-- ()
{
    ptr_--;
    return *this;
}


template<typename T>
const VectorIterator<T> VectorIterator<T>::operator++ (int)
{
    auto save = *this;
    ptr_++;
    return save;
}


template<typename T>
const VectorIterator<T> VectorIterator<T>::operator-- (int)
{
    auto save = *this;
    ptr_--;
    return save;
}


template<typename T>
VectorIterator<T> & VectorIterator<T>::operator+= (std::int64_t n)
{
    ptr_ += n;
    return *this;
}


template<typename T>
VectorIterator<T> & VectorIterator<T>::operator-= (std::int64_t n)
{
    ptr_ -= n;
    return *this;
}


template<typename T>
VectorIterator<T> VectorIterator<T>::operator+ (std::int64_t n) const
{
    return VectorIterator<T>(ptr_ + n);
}


template<typename T>
VectorIterator<T> VectorIterator<T>::operator- (std::int64_t n) const
{
    return VectorIterator<T>(ptr_ - n);
}


template<typename T>
typename VectorIterator<T>::reference
VectorIterator<T>::operator[] (std::int64_t n) const
{
    return *(ptr_ + n);
}


#endif //HW_CPP_VK_MY_ITERATOR_HPP
