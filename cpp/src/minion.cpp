/******************************************************************************
 *	Title:		Minion
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	09.08.2020.0
 ******************************************************************************/
#include <iostream>
#include <string>

#include <boost/exception/to_string.hpp>
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
    Singleton<Logger>::CleanUp();
}

void ilrd::Minion::Run()
{
    m_reactor.Run();
}

void ilrd::Minion::OnRequest(const Request& request)
{
    int m_index = be64toh(request.m_index);
    memset((void*)&m_response, 0, m_response.ResponseSize());

    std::string msg;
    if (0 == request.m_mode)
    {
        m_response.m_status =  m_storage.Read(m_index, (void*)m_response.m_data);
        switch(m_response.m_status)
        {
            case 0:
                msg += "Read from index ";
                msg += boost::to_string(m_index);
                LOG_INFO(msg);
                break;
            case 1:
                msg += "Failed to open storage";
                LOG_ERROR(msg);
                break;
            case 2:
                msg += "Failed to read from index ";
                msg += boost::to_string(m_index);
                LOG_ERROR(msg);
                break;
        }
    }
    else
    {
        m_response.m_status = m_storage.Write(m_index, (void*)request.m_data);
        switch(m_response.m_status)
        {
            case 0:
                msg += "Wrote to index ";
                msg += boost::to_string(m_index);
                LOG_INFO(msg);
                break;
            case 1:
                msg += "Failed to open storage";
                LOG_ERROR(msg);
                break;
            case 2:
                msg += "Failed to write to index ";
                msg += boost::to_string(m_index);
                LOG_ERROR(msg);
                break;
        }
    }
    
    m_response.m_uid = request.m_uid;
    m_response.m_mode = request.m_mode;

    m_comm.Reply(m_response);
}

/*****FUNCTION DEFINITION******/