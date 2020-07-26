/*******************************************************************************
 * File: scheduler.hpp - 	header file				 		     
 * Author: Yurii Yashchuk                                         
 * Reviewed by: Esti Binder				                                   			   *
 * Date: 23.07.2020		                                                           	   *
 ******************************************************************************/

#ifndef ILRD_RD8586_SCHEDULER_HPP
#define ILRD_RD8586_SCHEDULER_HPP

#include <boost/noncopyable.hpp>
#include <boost/chrono.hpp>
#include <boost/chrono/duration.hpp>
#include <queue>

#include "fd_timer.hpp"

namespace ilrd
{

// Responsibility:
// schedule tasks that will be executed in a future timepoint - interval from
// now or specific time - overload Add method
class Scheduler : private boost::noncopyable
{
public:
    // typedefs for inner types
    typedef FDTimer::MS MS;
    typedef boost::chrono::system_clock::time_point TimePoint;
    typedef FDTimer::ActionFunc ActionFunc;

    // Scheduler Constructor
    // Receives: reactor - a reference to a reactor to work with
    // Exceptions: throws runtime_error if timer file descriptor can't be
    //             created
    explicit Scheduler(Reactor& reactor);

    // Scheduler Destructor
    // Exceptions: no exceptions
    ~Scheduler();

    // Schedule Action
    // Receives: timepoint - a boost::chrono::system_clock::time_point object
    //                       with the time requested
    //           function - an function/functor to invoke at the timepoint
    // Exceptions: throws runtime_error if timer file descriptor can't be
    //             written
    void ScheduleAction(TimePoint timepoint, ActionFunc function);

    // Schedule Action
    // Receives: microseconds - a chrono::microseconds object with the time
    //           requested from now
    //           function - an function/functor to invoke at the timepoint
    // Exceptions: throws runtime_error if timer file descriptor can't be
    //             written
    void ScheduleAction(MS nanoseconds,
                        ActionFunc function); // boost::chrono::microseconds

    // Now
    // Return: TimePoint object with current system time
    // Exceptions: throws runtime_error if timer file descriptor can't be
    //             written
    static TimePoint Now();

private:
    struct Task
    {
        inline bool operator<(const Task& other_) const
        {
            return (!(m_timepoint < other_.m_timepoint));
        }

        TimePoint m_timepoint;
        ActionFunc m_function;
    };

    FDTimer m_timer;
    std::priority_queue< Task > m_tasks;
    void FlyYouFools(Handle fd);
};

////////////////////////////////////////////////////////////////////////////////
///   inline functions implementation   ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

} // namespace ilrd

#endif /* ILRD_RD8586_SCHEDULER_HPP */
