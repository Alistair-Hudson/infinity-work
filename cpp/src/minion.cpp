/******************************************************************************
 *	Title:		Minion
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	09.08.2020.0
 ******************************************************************************/
#include <iostream>

#include <boost/bind.hpp>

#include "minion.hpp"

/******MACROS******/


/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****STRUCTS*******/

/*****CLASSES******/

/*****FUNCTORS*****/

/******INTERNAL FUNCTION DECLARATION******/

/******CLASS METHODS*******/
/*======Minion=====*/
ilrd::Minion::Minion(int port, int num_of_blocks, int master_port):
                    m_reactor(),
                    m_comm(port, m_reactor, boost::bind(&Minion::OnRequest, this, _1)),
                    m_storage(num_of_blocks)                   
{

}
    
ilrd::Minion::~Minion()
{
    m_reactor.Stop();
}

void ilrd::Minion::Run()
{
    m_reactor.Run();
}

void ilrd::Minion::OnRequest(const Request& request)
{
    int m_index = be64toh(request.m_index);
    memset((void*)&m_response, 0, m_response.ResponseSize());

    if (0 == request.m_mode)
    {
        m_response.m_status =  m_storage.Read(m_index, (void*)m_response.m_data);
    }
    else
    {
        m_response.m_status = m_storage.Write(m_index, (void*)request.m_data);
    }
    
    m_response.m_uid = request.m_uid;
    m_response.m_mode = request.m_mode;

    m_comm.Reply(m_response);
}

/*****FUNCTION DEFINITION******/