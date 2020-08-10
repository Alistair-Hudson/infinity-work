/*******************************************************************************
 * File: master_communication.hpp -    header file for master communicator functions                     
 * Author: Yurii Yashchuk                                                          
 * Reviewed by:                       
 * Date: 05.08.2020                                                                
 ******************************************************************************/
#ifndef __ILRD_RD8586_MASTER_COMMUNICATOR_HPP__
#define __ILRD_RD8586_MASTER_COMMUNICATOR_HPP__

#include <boost/noncopyable.hpp> // boost::noncopyable
#include <boost/function.hpp> /* function */

#include "udp_connector.hpp"
#include "reactor_w_callback.hpp"
#include "protocol.hpp"
#include "callback.hpp"

namespace ilrd
{
    class MasterCommunicator:private boost::noncopyable
    {
    public:
        typedef boost::function <void (const Request&) > ActionRequest;
        explicit MasterCommunicator(int port, Reactor& reactor, 
            ActionRequest ar_func);
        ~MasterCommunicator();
        // ReadRequest Function (added to reactor)
        // Receives: file descriptor.
        // Returns: nothing
        void ReadRequest(int fd);

        // Reply Function
        // Receives: const refernce to class Response.
        // Returns: nothing
        void Reply(const Response& res) const;

    private:
        ActionRequest m_ar_func;
        UDPConnector m_con;
        Reactor& m_reactor;
        Callback< Source< int > > m_callback;
        Request m_request;
        const int m_port;
        struct sockaddr_in m_master_addr;   
    };

} // namespace ilrd

#endif /* __ILRD_RD8586_MASTER_COMMUNICATOR_HPP__ */