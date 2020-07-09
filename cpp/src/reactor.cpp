/******************************************************************************
 *	Title:		Reactor
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	08.06.2020.0
 ******************************************************************************/

#include <sys/select.h> /* select, FD Macros */

#include "reactor.hpp"

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/
static bool g_running = 0;

/*****STRUCTS*******/

/*****CLASSES******/

/*****FUNCTORS*****/

/******CLASS METHODS*******/
/*=====IListener=====*/

/*=====Reactor=====*/
void Reactor::Add(HandleAndMode handle_and_mode, HandleFunc func)
{
    m_EventHandlers.insert(std::make_pair(handle_and_mode, func));
}

void Reactor::Remove(HandleAndMode handle_and_mode)
{
    m_EventHandlers.erase(m_EventHandlers.find(handle_and_mode));
}

void Reactor::Run()
{
    g_running = 1;
    std::vector<HandleAndMode> eventVector;

    std::map<HandleAndMode, HandleFunc>::iterator mapIterator;

    while (g_running)
    {
        eventVector.clear();
        //push events into a vector for checking
        for (mapIterator = m_EventHandlers.begin(); 
            mapIterator != m_EventHandlers.end(); 
            mapIterator = next(mapIterator, 1))
        {
            eventVector.push_back(mapIterator->first);
        }
        // call listener
        eventVector = m_Listener->Listen(eventVector);
        //run all active functions
        while (!eventVector.empty())
        {
            m_EventHandlers.find(eventVector.back())->second(eventVector.back().second);
            eventVector.pop_back();
        }
    }
}

void Reactor::Stop()
{
    g_running = 0;
}

Reactor::~Reactor()
{
    m_EventHandlers.clear();
}

/******INTERNAL FUNCTION DECLARATION******/

/*****FUNCTION DEFINITION******/