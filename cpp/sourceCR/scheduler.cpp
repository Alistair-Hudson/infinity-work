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
ilrd::Scheduler::Scheduler(Reactor& reactor)
{
    FDTimer m_timer(reactor, 
                    boost::bind(&Scheduler::FlyYouFools, this, _1));
    
}
ilrd::Scheduler::~Scheduler()
{

}

void ilrd::Scheduler::ScheduleAction(TimePoint timepoint, 
                                    ActionFunc function)
{
    MS fromNow = timepoint - Now();

    m_timer.Set(fromNow);

    Task newTask;
    newTask.m_function = function;
    newTask.m_timepoint = TimePoint(fromNow);

    m_tasks.push(newTask);
}

void ilrd::Scheduler::ScheduleAction(MS nanoseconds,
                                     ActionFunc function)
{

    m_timer.Set(nanoseconds);

    Task newTask;
    newTask.m_function = function;
    newTask.m_timepoint = TimePoint(nanoseconds + Now());

    m_tasks.push(newTask);
}

ilrd::Scheduler::TimePoint ilrd::Scheduler::Now()
{
    return boost::chrono::steady_clock::now();//the current time;
}

void ilrd::Scheduler::FlyYouFools()
{

}

/*****FUNCTION DEFINITION******/
