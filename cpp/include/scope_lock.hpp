#ifndef __SHARED_POINTER_HPP__
#define __SHARED_POINTER_HPP__

/*******************************************************************************
                                * API FOR SCOPE LOCK
                                * version 01.07.2020.0
******************************************************************************/
#include <iostream>
#include <thread>
#include <mutex>

namespace irld
{
class NonCopy
{
public: 
    NonCopy(){}
    ~NonCopy(){}
private:
    NonCopy(const NonCopy&) = delete;
    NonCopy& operator=(const NonCopy&) = delete;
};

template<typename Container>
class ScopeLock : public NonCopy
{
public:
    ScopeLock(Container&);
    ~ScopeLock();
    
private:
    Container& m_c;
};
};

#endif /* __SHARED_POINTER_HPP__ */