/*******************************************************************************
 * File: timer.hpp - header for timer functions	implementation			 		     
 * Author: Yurii Yashchuk                                     
 * Reviewed by: Esti Binder		                                   			   
 * Date: 23.07.2020		                                                           	   *
 ******************************************************************************/

#include <iostream>
#include "fd_timer.hpp"

using namespace ilrd;

FDTimer::FDTimer(Reactor& reactor, ActionFunc callback_func):
                m_reactor(reactor), m_callback(callback_func),
                m_fd(timerfd_create(CLOCK_REALTIME, 0))
{
    if (-1 == m_fd)
    {
        throw "Timer file descriptor can't be created!"; 
    }
    ModeAndHandle handle_and_mode;
    handle_and_mode.first = READ; 
    handle_and_mode.second = m_fd;
    m_reactor.Add(handle_and_mode, &m_callback);
}

FDTimer::~FDTimer()
{
    ModeAndHandle handle_and_mode;
    handle_and_mode.first = READ; 
    handle_and_mode.second = m_fd;
    m_reactor.Remove(handle_and_mode);
    close(m_fd);
}

void FDTimer::Set(MS milliseconds)
{
    struct itimerspec new_value;
    new_value.it_value.tv_sec = milliseconds.count()/1000;
    new_value.it_value.tv_nsec = (milliseconds.count()%1000) *1000000;

    new_value.it_interval.tv_sec = 0;
    new_value.it_interval.tv_nsec = 0;

    if (-1 == timerfd_settime(m_fd, 0, &new_value, NULL))
    {
        throw ("timerfd_settime did not work");
    }

}
void FDTimer::Unset()
{
    struct itimerspec new_value;
    new_value.it_value.tv_sec = 0;
    new_value.it_value.tv_nsec = 0;

    new_value.it_interval.tv_sec = 0;
    new_value.it_interval.tv_nsec = 0;  

    if (-1 == timerfd_settime(m_fd, 0, &new_value, NULL))
    {
        throw ("timerfd_settime did not work");
    }    
}


 