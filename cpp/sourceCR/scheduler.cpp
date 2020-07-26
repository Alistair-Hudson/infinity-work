/*******************************************************************************
 * File: scheduler.cpp - header for scheduler functions			 		     
 * Author: Yurii Yashchuk                                     
 * Reviewed by: Esti Binder		                                   			   
 * Date: 23.07.2020		                                                           	   *
 ******************************************************************************/

#include "scheduler.hpp"

using namespace ilrd;
using namespace std;

Scheduler::Scheduler(Reactor& reactor): m_timer
                    (reactor, boost::bind(&Scheduler::StartTask, this, _1))
{
}

Scheduler::~Scheduler()
{
}

void Scheduler::ScheduleAction(MS milliseconds, ActionFunc function)
{
    Task new_task;
    new_task.m_timepoint =  milliseconds + Now();
    new_task.m_function = function;    
    m_tasks.push(new_task);
    if (m_tasks.top().m_timepoint == new_task.m_timepoint)
    {
        m_timer.Set(milliseconds);
    }
}

void Scheduler::ScheduleAction(TimePoint timepoint, ActionFunc function)
{
    Task new_task;
    new_task.m_timepoint = timepoint;
    new_task.m_function = function;    
    m_tasks.push(new_task);

    if (m_tasks.top().m_timepoint == timepoint)
    {
        m_timer.Set(boost::chrono::duration_cast<MS>
        (timepoint - Now()));
    }
}


Scheduler::TimePoint Scheduler::Now()
{
    return boost::chrono::system_clock::now();
}

void Scheduler::StartTask(Handle fd)
{
    if (!m_tasks.empty())
    {   
        Task executable = m_tasks.top();    
        executable.m_function(fd);
        m_tasks.pop();
        if (m_tasks.empty())
        {
            m_timer.Unset();
        }
        else
        {
            executable = m_tasks.top();            
            m_timer.Set(boost::chrono::duration_cast<MS> 
            (executable.m_timepoint - Now()));
        }
    }
}