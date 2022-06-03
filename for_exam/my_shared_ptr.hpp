#ifndef HW_CPP_VK_MY_SHARED_PTR_HPP
#define HW_CPP_VK_MY_SHARED_PTR_HPP


#include <cstdint>
#include <stdexcept>


template<typename T>
class SharedPtr
{
public:
    SharedPtr();
    explicit SharedPtr(T * ptr);
    SharedPtr(const SharedPtr & other);
    SharedPtr & operator= (const SharedPtr & other);
    ~SharedPtr();

    void reset();
    void reset(T * ptr);

    T * operator-> () const;
    T & operator* () const;

    T * get() const;

private:

    void inc_counter();
    void dec_counter();

    T * ptr_;
    int64_t * ref_count_;
};


template<typename T>
SharedPtr<T>::SharedPtr() : ptr_(nullptr), ref_count_(nullptr) {}


template<typename T>
SharedPtr<T>::SharedPtr(T * ptr) : ptr_(ptr), ref_count_(nullptr)
{
    ref_count_ = new int64_t;
    if (!ref_count_) throw std::bad_alloc();
    *ref_count_ = 1;
}


template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr & other) :
ptr_(other.ptr_), ref_count_(other.ref_count_)
{
    if (!ptr_) return;
    inc_counter();
}


template<typename T>
SharedPtr<T> & SharedPtr<T>::operator= (const SharedPtr<T> & other)
{
    if (this == &other)
    {
        return *this;
    }

    ptr_ = other.ptr_;
    ref_count_ = other.ref_count_;

    if (!other.ptr_)
    {
        return *this;
    }

    inc_counter();
    return *this;
}


template<typename T>
void SharedPtr<T>::reset()
{
    if (!ptr_) return;
    dec_counter();
    ref_count_ = nullptr;
    ptr_ = nullptr;
}


template<typename T>
void SharedPtr<T>::reset(T * ptr)
{
    reset();
    ref_count_ = new int64_t;
    if (!ref_count_) throw std::bad_alloc();
    *ref_count_ = 1;
    ptr_ = ptr;
}


template<typename T>
void SharedPtr<T>::inc_counter()
{
    if (!ref_count_) throw std::exception();
    ++(*ref_count_);
}


template<typename T>
void SharedPtr<T>::dec_counter()
{
    if (ref_count_ == nullptr) throw std::exception();
    --(*ref_count_);
    if (*ref_count_ == 0)
    {
        auto save_ref = ref_count_;
        auto save_ptr = ptr_;
        ptr_ = nullptr;
        ref_count_ = nullptr;
        delete save_ref;
        delete save_ptr;
    }
}


template<typename T>
T * SharedPtr<T>::operator->() const
{
    return ptr_;
}


template<typename T>
T & SharedPtr<T>::operator*() const
{
    return *ptr_;
}


template<typename T>
T * SharedPtr<T>::get() const
{
    return ptr_;
}



template<typename T>
SharedPtr<T>::~SharedPtr()
{
    if (!ptr_) return;
    dec_counter();
    ptr_ = nullptr;
    ref_count_ = nullptr;
}



#endif //HW_CPP_VK_MY_SHARED_PTR_HPP
