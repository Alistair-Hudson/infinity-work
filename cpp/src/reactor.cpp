/******************************************************************************
 *	Title:		Reactor
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	08.06.2020.0
 ******************************************************************************/


#include "reactor.hpp"


/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****STRUCTS*******/

/*****CLASSES******/

/******CLASS METHODS*******/
/*=====Reactor=====*/
void Reactor::Add(Handle handle, MODE mode, HandleFunc func)
{
    HandleAndMode event(mode, handle);
    m_EventHandlers.insert(pair<HandleAndMode, std::vector<HandleFunc>(event, func));
}

void Reactor::Remove(Handle handle, MODE mode, HandleFunc func)
{
    m_EventHandlers.erase(m_EventHandlers.find());
}

void Reactor::Run()
{

}

void Reactor::Stop()
{

}

Reactor::~Reactor()
{

}

/******INTERNAL FUNCTION DECLARATION******/

/*****FUNCTION DEFINITION******/