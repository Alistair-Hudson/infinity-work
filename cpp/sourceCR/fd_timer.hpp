/*******************************************************************************
 * File: timer.hpp - header for timer functions			 		     
 * Author: Yurii Yashchuk                                     
 * Reviewed by: Esti Binder		                                   			   
 * Date: 23.07.2020		                                                           	   *
 ******************************************************************************/

#ifndef ILRD_RD8586_FD_TIMER_HPP
#define ILRD_RD8586_FD_TIMER_HPP

#include <boost/chrono.hpp>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/bind.hpp>
#include <sys/timerfd.h>

#include "source_callback.hpp"
#include "advanced_reactor.hpp"

namespace ilrd
{

// use #include <sys/timerfd.h> in the implementation
class FDTimer : private boost::noncopyable
{
public:
    // typedefs for inner types
    typedef Callback< Source< int > >::NotifyFunction ActionFunc;
    typedef boost::chrono::milliseconds MS;

    // FDTimer Constructor
    // Receives: reactor - a reference to a reactor to work with
    //           callback_func - a handler function to invoke when the reactor
    //                           calls timer file descriptors' handler
    // Exceptions: throws runtime_error if timer file descriptor can't be
    //             created
    explicit FDTimer(Reactor& reactor, ActionFunc callback_func);

    // FDTimer Destructor
    // Exceptions: no exceptions
    ~FDTimer();

    // Set
    // Receives: microseconds - a chrono::microseconds object with the time
    //           requested from now
    // Exceptions: throws runtime_error if timer file descriptor can't be
    //             written
    void Set(MS milliseconds);

    // Unset
    // Exceptions: throws runtime_error if timer file descriptor can't be
    //             written
    void Unset();

private:
    Reactor& m_reactor;
    Callback< Source< int > > m_callback;
    int m_fd;
};

////////////////////////////////////////////////////////////////////////////////
///   inline functions implementation   ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

} // namespace ilrd

#endif /* ILRD_RD8586_FD_TIMER_HPP */
