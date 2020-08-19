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
    Singleton<Factory<int, BaseCommand, Params > >::GetInstance()->Add(0, &ilrd::ReadBuilder);
    Singleton<Factory<int, BaseCommand, Params > >::GetInstance()->Add(1, &ilrd::WriteBuilder);
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
    Params new_params = {m_storage, m_response, request};
    (*Singleton<Factory<int, BaseCommand, Params > >::GetInstance()->Create(request.m_mode, new_params))();
    
    m_response.m_uid = request.m_uid;
    m_response.m_mode = request.m_mode;

    m_comm.Reply(m_response);
}

/*****FUNCTION DEFINITION******/