/******************************************************************************
 *	Title:		Reactor
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	08.06.2020.0
 ******************************************************************************/

#include <boost/foreach.hpp> /* BOOST_FOREACH */

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
    //link src/cb
}

void Reactor::Remove(HandleAndMode handle_and_mode)
{
    m_EventHandlers.erase(m_EventHandlers.find(handle_and_mode));
    //delink src/cb
}

void Reactor::Run()
{
    g_running = 1;
    std::vector<HandleAndMode> eventVector;

    while (g_running && !m_EventHandlers.empty())
    {
        eventVector.clear();
        std::pair<HandleAndMode, std::vector<HandleFunc>> mapIterator;
        //push events into a vector for checking
        BOOST_FOREACH(mapIterator, m_EventHandlers)
        {
            eventVector.push_back(mapIterator.first);
        }
        // call listener
        eventVector = m_Listener->Listen(eventVector);
        //run all active functions
        BOOST_FOREACH(HandleAndMode handle, eventVector)
        {
            BOOST_FOREACH(HandleFunc handler, m_EventHandlers[handle])
            {
                handler(handle.second);
            }
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
    //while (conatiner not empty)
    //{
        //Delink link iterator
        //remove iterator
        //next iterator
    //}
}

/******INTERNAL FUNCTION DECLARATION******/

/*****FUNCTION DEFINITION******/