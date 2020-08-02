#ifndef __ILRD_RD8586_SINGLETON_HPP__
#define __ILRD_RD8586_SINGLETON_HPP__
/*******************************************************************************
                                * API FOR Singleton
                                * version 02.08.2020.0
******************************************************************************/
#include <iostream>
#include <thread>
#include <atomic>

#include <boost/atomic.hpp>

#include "boost/core/noncopyable.hpp"

namespace ilrd
{

template < class T >
class Singleton: private boost::noncopyable
{
public:

    static T* GetInstance();
    static void CleanUp();

private:
    Singleton()
    {}
    static T * m_instance;
};

template<typename T> 
T* Singleton<T>::m_instance = nullptr;

bool lock = 0;

template < class T >
T *Singleton<T>::GetInstance()
{
    
    if(NULL == m_instance)
    {
        boost::atomic_thread_fence(boost::memory_order_acquire);
        //lock
        while (__atomic_test_and_set(&lock, 1))
        {
            //spin lock
        }
        
        if (NULL == m_instance)
        {

            m_instance = new T;

        }
        lock = 0;
        boost::atomic_thread_fence(boost::memory_order_release);
    }
    
    return m_instance;
}

template<class T> 
void Singleton<T>::CleanUp()
{
    delete m_instance;
}
} // namespace ilrd



#endif /* __ILRD_RD8586_SINGLETON_HPP__ */