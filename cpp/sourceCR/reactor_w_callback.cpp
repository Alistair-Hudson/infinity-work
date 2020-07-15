/******************************************************************************
 *	Title:		Reactor
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	08.06.2020.0
 ******************************************************************************/

#include <boost/foreach.hpp> /* BOOST_FOREACH */

#include "reactor_w_callback.hpp"

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/
static bool g_running = 0;

/*****STRUCTS*******/

/*****CLASSES******/

/*****FUNCTORS*****/

/******INTERNAL FUNCTION DECLARATION******/
static void AddToVector(Handle fd, vector<Source<int>>* vector, Source<int>* src);

/******CLASS METHODS*******/
/*=====Reactor=====*/
void Reactor::Add(MODE mode, Handle fd, Callback<Source<int>>* callback)
{
    Source<int>* newSrc = new Source<int>;
    newSrc->Subscribe(callback);
    
    switch(mode)
    {
        case (READ):
            AddToVector(fd, &m_read, newSrc);
            break;
        case (WRITE):
            AddToVector(fd, &m_write, newSrc);
            break;
        case (EXCEPTION):
            AddToVector(fd, &m_exception, newSrc);
            break;
    }
}

void Reactor::Remove(MODE mode, Handle fd)
{   
    Source<int> src*;

    switch(mode)
    {
        case (READ):
            src = m_read.at(fd);
            m_read.at(fd) = NULL;
            break;
        case (WRITE):
            src = m_write.at(fd);
            m_write.at(fd) = NULL;
            break;
        case (EXCEPTION):
            src = m_exception.at(fd);
            m_exception.at(fd) = NULL;
            break;
    }
    if (NULL != src)
    {
        src->Unsubscribe(NULL);
    }
}

void Reactor::Run()
{
    g_running = 1;

    while (g_running && (!m_read.empty() || !m_write.empty()))
    {
        std::vector<Source<int>> readVector = m_read;
        std::vector<Source<int>> writeVector = m_write;
        std::vector<Source<int>> exceptionVector = m_exception;
        int fd = 0;
        // call listener
        m_Listener->Listen(readVector, writeVector, exceptionVector);
        //run all active functions
        BOOST_FOREACH(Source<int>* handle, readVector)
        {
            if (NULL != handle)
            {
                handle->Notify(fd)
                ++fd;
            }
        }
        fd = 0;
        BOOST_FOREACH(Source<int>* handle, writeVector)
        {
            if (NULL != handle)
            {
                handle->Notify(fd)
                ++fd;
            }
        }
        fd = 0;
        BOOST_FOREACH(Source<int>* handle, exceptionVector)
        {
            if (NULL != handle)
            {
                handle->Notify(fd)
                ++fd;
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
    BOOST_FOREACH(Source<int>* handle, m_read)
    {
        if (NULL != handle)
        {
            handle->Unsuscribe(NULL);
        }
        
    }
    m_read.clear();
    BOOST_FOREACH(Source<int>* handle, m_write)
    {
        if (NULL != handle)
        {
            handle->Unsuscribe(NULL);
        }
    }
    m_write.clear();
    BOOST_FOREACH(Source<int>* handle, m_exception)
    {
        if (NULL != handle)
        {
            handle->Unsuscribe(NULL);
        }
    }
    m_exception.clear();

}

/*****FUNCTION DEFINITION******/
static void AddToVector(Handle fd, vector<Source<int>> vector, Source<int> src)
{
    if (fd > vector->size())
    {
        vector->resize(fd, NULL);
    }
    vector->insert(vector.begin()+fd, src)
}
