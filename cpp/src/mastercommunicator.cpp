/******************************************************************************
 *	Title:		Master Communcitor
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	06.08.2020.0
 ******************************************************************************/
#include <iostream>

#include <boost/bind.hpp>

#include "mastercommunicator.hpp"

/******MACROS******/
#define WRITE_RESPONSE_BYTES (10)

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****STRUCTS*******/

/*****CLASSES******/

/*****FUNCTORS*****/

/******INTERNAL FUNCTION DECLARATION******/

/******CLASS METHODS*******/
/*======MasterCommunicator=====*/
ilrd::MasterCommunicator::MasterCommunicator(int port, 
                                            Reactor& reactor, 
                                            ActionRequest ar_func):
                                                m_ar_func(ar_func),
                                                m_con(port), 
                                                m_reactor(reactor),
                                                m_callback(boost::bind(&MasterCommunicator::ReadRequest, this, _1)), 
                                                m_port(port)
{
    m_reactor.Add(READ, m_con.GetFD(), &m_callback);
    memset((void*)&m_master_addr, 0, sizeof(m_master_addr));
    
}

ilrd::MasterCommunicator::~MasterCommunicator()
{
    m_reactor.Remove(READ, m_con.GetFD());
}

void ilrd::MasterCommunicator::ReadRequest(int fd)
{

    socklen_t length =sizeof(struct sockaddr_in);
    int bytes_received; 

    memset((void*)&m_request, 0, m_request.RequestSize());

    if (0 > (bytes_received = recvfrom(  m_con.GetFD(), 
                                        (char *)&m_request, 
                                        m_request.RequestSize(),  
                                        MSG_WAITALL, 
                                        ( struct sockaddr *) &m_master_addr, 
                                        &length)))
    {
        throw std::runtime_error("failed to receive data\n");    
    }

    m_ar_func(m_request);
    (void)fd;
}

void ilrd::MasterCommunicator::Reply(const Response& res) const
{
    std::cout << "sending reply\n";
    size_t bytes = res.ResponseSize();

    if (1 == res.m_mode)
    {
        bytes = WRITE_RESPONSE_BYTES;
    }

    if(0 > sendto(  m_con.GetFD(), 
                    &res, 
                    bytes,  
                    MSG_CONFIRM, 
                    (const struct sockaddr *) &m_master_addr, 
                    sizeof(struct sockaddr_in)))
    {
        throw std::runtime_error("Failed to send response\n");
    }

    std::cout<< "reply sent\n";
}

/*****FUNCTION DEFINITION******/