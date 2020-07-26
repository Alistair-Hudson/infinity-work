/******************************************************************************
 *	Title:		FDTimer
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	23.07.2020.0
 ******************************************************************************/

#include <sys/timerfd.h>

#include "fd_timer.hpp"

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****STRUCTS*******/

/*****CLASSES******/

/*****FUNCTORS*****/

/******INTERNAL FUNCTION DECLARATION******/

/******CLASS METHODS*******/
/*===FDTimer===*/
ilrd::FDTimer::FDTimer(Reactor& reactor, ActionFunc callback_func): m_reactor(reactor), 
                                                                    m_callback(callback_func)
{
    if (0 > (m_fd = timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK)))
    {
        throw "Failed to open fd for timer:";
    }
    m_reactor.Add(READ, m_fd, &m_callback);
}

ilrd::FDTimer::~FDTimer()
{
  //  m_reactor.Remove(READ, m_fd);
}

void ilrd::FDTimer::Set(ilrd::FDTimer::MS nanoseconds)
{

    struct itimerspec newSet;
    newSet.it_interval.tv_sec = 0;
    newSet.it_interval.tv_nsec = 0;
    newSet.it_value.tv_sec = nanoseconds.count() / 1000000000;
    newSet.it_value.tv_nsec = nanoseconds.count() % 1000000000;
    timerfd_settime(m_fd, TFD_TIMER_ABSTIME, &newSet, NULL);
}

void ilrd::FDTimer::Unset()
{
    struct itimerspec newSet;
    newSet.it_interval.tv_sec = 0;
    newSet.it_interval.tv_nsec = 0;
    newSet.it_value.tv_sec = 0;
    newSet.it_value.tv_nsec = 0;
    timerfd_settime(m_fd, TFD_TIMER_ABSTIME, &newSet, NULL);
}

/*****FUNCTION DEFINITION******/
