#ifndef ILRD_RD8586_WAIT_TABLE_HPP
#define ILRD_RD8586_WAIT_TABLE_HPP
/*****************************************************************************
 * API Wait Table
 * Alistair Hudson
 * version 12.08.2020.0
******************************************************************************/

#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/noncopyable.hpp>

namespace ilrd
{

template <class QUEUE, typename T >
class WaitableQueue : private boost::noncopyable
{
public:
    // default Ctor and Dtor
    typedef boost::posix_time::milliseconds Millisec;
    void Push (const T& val);
    void Pop(T& peaked_value); // will use front and pop
    bool Pop(T& peaked_value, Millisec timeout);
    bool Empty() const; //please make sur to use in a thread-safe environment
private:
    QUEUE m_queue;
    boost::condition_variable m_pushflag; //use boost::unique_lock
    boost::mutex m_mutex;//use boost::unique_lock
};

template <class QUEUE, typename T >
void WaitableQueue<QUEUE, T>::Push (const T& val)
{
    boost::unique_lock<boost::mutex> lock(m_mutex);
    m_queue.push(val);
    m_pushflag.notify_one();
}

template <class QUEUE, typename T >
void WaitableQueue<QUEUE, T>::Pop(T& peaked_value)
{
    boost::unique_lock<boost::mutex> lock(m_mutex);
    if (!m_queue.empty())
    {
        peaked_value = m_queue.front();
        m_queue.pop();
        return;
    }
    
    m_pushflag.wait(lock);
    peaked_value = m_queue.front();
    m_queue.pop();
}

template <class QUEUE, typename T >
bool WaitableQueue<QUEUE, T>::Pop(T& peaked_value, Millisec timeout)
{
    boost::system_time wait_until = 
                                boost::get_system_time() + timeout;
    boost::unique_lock<boost::mutex> lock(m_mutex);
    if (!m_queue.empty())
    {
        peaked_value = m_queue.front();
        m_queue.pop();
        return 1;
    }

    if ( m_pushflag.timed_wait(lock, wait_until))
    {
        peaked_value = m_queue.front();
        m_queue.pop();
        return 1;
    }
    return 0;
}

template <class QUEUE, typename T >
bool WaitableQueue<QUEUE, T>::Empty() const
{
    boost::unique_lock<boost::mutex> lock(m_mutex);
    return m_queue.empty();
 
}

}// namespace ilrd

#endif /* __ILRD_RD8586_STORAGE_HPP__ */