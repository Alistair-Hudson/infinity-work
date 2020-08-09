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
    
}

ilrd::MasterCommunicator::~MasterCommunicator()
{
    m_reactor.Remove(READ, m_con.GetFD());
}

void ilrd::MasterCommunicator::ReadRequest(int fd)
{

    socklen_t length;
    int bytes_received; 
    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET; 
    server_addr.sin_addr.s_addr = INADDR_ANY; 
    server_addr.sin_port = htons(m_port);

    memset((void*)&m_request, 0, m_request.RequestSize());

    if (0 > (bytes_received = recvfrom(  m_con.GetFD(), 
                                        (char *)&m_request, 
                                        m_request.RequestSize(),  
                                        MSG_WAITALL, 
                                        ( struct sockaddr *) &server_addr, 
                                        &length)))
    {
        throw "failed to receive data\n";    
    }

    m_ar_func(m_request);
    (void)fd;
}

void ilrd::MasterCommunicator::Reply(const Response& res) const
{
    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET; 
    server_addr.sin_addr.s_addr = INADDR_ANY; 
    server_addr.sin_port = htons(m_port);

    if(0 > sendto(  m_con.GetFD(), 
                    (const char *)&res, 
                    res.ResponseSize(),  
                    MSG_CONFIRM, 
                    (const struct sockaddr *) &server_addr, 
                    sizeof(server_addr)))
    {
        throw "Failed to send response\n";
    }
}

/*****FUNCTION DEFINITION******/