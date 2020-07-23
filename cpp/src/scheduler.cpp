/******************************************************************************
 *	Title:		Scheduler
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	21.07.2020.0
 ******************************************************************************/

#include <boost/bind.hpp>

#include "scheduler.hpp"

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****STRUCTS*******/

/*****CLASSES******/

/*****FUNCTORS*****/

/******INTERNAL FUNCTION DECLARATION******/

/******CLASS METHODS*******/
ilrd::Scheduler::Scheduler(Reactor& reactor): m_timer(reactor, 
                                                boost::bind(&Scheduler::FlyYouFools, this, _1))
{
   /* FDTimer m_timer(reactor, 
                    boost::bind(&Scheduler::FlyYouFools, this, _1));
    */
}
ilrd::Scheduler::~Scheduler()
{

}

void ilrd::Scheduler::ScheduleAction(TimePoint timepoint, 
                                    ActionFunc function)
{

    MS wait = (timepoint - Now());


    if (m_tasks.empty() || timepoint < m_tasks.top().m_timepoint)
    {
        m_timer.Set(wait);
    }

    Task new_task;
    new_task.m_function = function;
    new_task.m_timepoint = timepoint;

    m_tasks.push(new_task);
    
}

void ilrd::Scheduler::ScheduleAction(MS nanoseconds,
                                     ActionFunc function)
{
TimePoint insert = TimePoint(nanoseconds + Now());


    if (m_tasks.empty() || insert < m_tasks.top().m_timepoint)
    {
        m_timer.Set(nanoseconds);
    }


    Task new_task;
    new_task.m_function = function;
    new_task.m_timepoint = insert;

    m_tasks.push(new_task);
}

ilrd::Scheduler::TimePoint ilrd::Scheduler::Now()
{
    return boost::chrono::system_clock::now();//the current time;
}

void ilrd::Scheduler::FlyYouFools(int fd)
{
    if (m_tasks.empty())
    {
        return;
    }

    m_tasks.top().m_function(fd);
    m_tasks.pop();

}

/*****FUNCTION DEFINITION******/
