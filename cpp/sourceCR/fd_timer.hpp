/*******************************************************************************
 * File: timer.hpp - 	header file				 		     *
 * Author: Yehuda Levavi                                         *
 * Reviewed by: 				                                   			   *
 * Date: 		                                                           	   *
 ******************************************************************************/

#ifndef ILRD_RD8586_FD_TIMER_HPP
#define ILRD_RD8586_FD_TIMER_HPP

#include <boost/chrono.hpp>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>

#include "callback.hpp"
#include "reactor_w_callback.hpp"

namespace ilrd
{


class FDTimer : private boost::noncopyable
{
public:
    // typedefs for inner types
    typedef Callback< Source< int > >::CallbackPointer ActionFunc;
    typedef boost::chrono::nanoseconds MS;

    // FDTimer Constructor
    // Receives: reactor - a reference to a reactor to work with
    //           callback_func - a handler function to invoke when the reactor
    //                           calls timer file descriptors' handler
    // Exceptions: throws runtime_error if timer file descriptor can't be
    //             created
    explicit FDTimer(Reactor& reactor, ActionFunc& callback_func);

    // FDTimer Destructor
    // Exceptions: no exceptions
    ~FDTimer();

    // Set
    // Receives: milliseconds - a chrono::miliiseconds object with the time
    //           requested from now
    // Exceptions: throws runtime_error if timer file descriptor can't be
    //             written
    void Set(MS nanoseconds);

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
