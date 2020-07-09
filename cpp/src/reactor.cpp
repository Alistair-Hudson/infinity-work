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
static struct timeval TIMEOUT = {7, 0};

/*****STRUCTS*******/

/*****CLASSES******/

/*****FUNCTORS*****/
class Count
{
public:
    Count(int* read, int* write, int* excep):m_read(read), m_write(write), m_excep(excep){}
    void operator() (const HandleAndMode& handle)
    {
        switch(handle.first)
        {
            case(READ):
                ++*m_read;
                break;
            case(WRITE):
                ++*m_write;
                break;
            case(EXCEPTION):
                ++*m_excep;
                break;
            default:
                break;
        }
    }

private:
    int* m_read;
    int* m_write;
    int* m_excep;
};

class SetSet
{
public:
    SetSet(fd_set* read, fd_set* write, fd_set* excep):m_read(read), m_write(write), m_excep(excep){}
    void operator() (const HandleAndMode& handle)
    {
        switch(handle.first)
        {
            case(READ):
                FD_SET(handle.second, m_read);
                break;
            case(WRITE):
                FD_SET(handle.second, m_write);
                break;
            case(EXCEPTION):
                FD_SET(handle.second, m_excep);
                break;
            default:
                break;
        }
    }

private:
    fd_set* m_read;
    fd_set* m_write;
    fd_set* m_excep;
};

/******CLASS METHODS*******/
/*=====IListener=====*/
std::vector<HandleAndMode> IListener::Listen(const std::vector<HandleAndMode>& handle)
 {
    int read_count = 0;
    int write_count = 0;
    int excep_count = 0;
    //count the number of read, write, and exception file desscriptors
    for_each(handle.begin(), handle.end(), Count(&read_count, &write_count, &excep_count));

    fd_set* read_set = new fd_set[read_count];
    fd_set* write_set = new fd_set[write_count];
    fd_set* excep_set = new fd_set[excep_count];
    //set file descriptors into each of the fd sets
    for_each(handle.begin(), handle.end(), SetSet(read_set, write_set, excep_set));
 
    //see which fds are active
    int activeEvents = select(read_count + write_count + excep_count + 1,
                              read_set, write_set, excep_set, &TIMEOUT);
    std::vector<HandleAndMode> output;
    if(0 > activeEvents)
    {
        std::cout << "Select Error" << std::endl;
        g_running = 0;
    }
    else if(0 == activeEvents)
    {
        std::cout << "Listening Time out" << std::endl;
    }
    else
    {
        //add read to output
        for (int fd = 0; fd < read_count; ++fd)
        {
            if(FD_ISSET(fd, read_set))
            {
                output.push_back(std::make_pair(READ, fd));
            }
        }
        //add write to output
        for (int fd = 0; fd < write_count; ++fd)
        {
            if(FD_ISSET(fd, write_set))
            {
                output.push_back(std::make_pair(WRITE, fd));
            }
        }
        //add exception to output
        for (int fd = 0; fd < excep_count; ++fd)
        {
            if(FD_ISSET(fd, excep_set))
            {
                output.push_back(std::make_pair(EXCEPTION, fd));
            }
        }

    }
    delete[] read_set;
    delete[] write_set;
    delete[] excep_set;

    return output;
 }


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
        TIMEOUT.tv_sec = 7;
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