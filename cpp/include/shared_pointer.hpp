#ifndef __SHARED_POINTER_HPP__
#define __SHARED_POINTER_HPP__

/*******************************************************************************
                                * API FOR SHARED POINTER
                                * version 30.06.2020.0
******************************************************************************/
#include <iostream>

template <typename T>
class SharedPointer
{
public:
    explicit SharedPointer(T *m_ptr);
    SharedPointer(const SharedPointer<T> &other_);
    SharedPointer &operator=(const SharedPointer<T> &other);
    ~SharedPointer();

    template <typename C> // Used for upcasting
    SharedPointer(const SharedPointer<C> &other_);
    template <typename C>
    SharedPointer &operator=(const SharedPointer<C> &other);

    T *operator->() const; // can be applied on both const and not const obj

    T &operator*() const;

private:
    int *counter;
    T *m_pointer;

};

#endif /* __SHARED_POINTER_HPP__ */