/******************************************************************************
 *	Title:		Reactor
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	08.06.2020.0
 ******************************************************************************/

#include <boost/shared_ptr.hpp> /* boost::shared_ptr */
#include <boost/make_shared.hpp> /* boost::make_shared */

#include "reactor_w_callback.hpp"

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/
static bool g_running = 0;


/*****STRUCTS*******/

/*****CLASSES******/

/*****FUNCTORS*****/
class PushToVector
{
public:
    PushToVector(std::vector< Handle >* v):m_v(v){}
    void operator() (std::pair< Handle, boost::shared_ptr< Source< int > > > handle)
    {
        m_v->push_back(handle.first);
    }
private:
    std::vector<Handle>* m_v;
};

class CallNotify
{
public:
    CallNotify(std::map< Handle, boost::shared_ptr< Source< int > > >* map):m_map(map){}
    void operator() (Handle fd)
    {
        boost::shared_ptr< Source< int > > handle = m_map->find(fd)->second;
        handle->Notify(fd);
    }
private:
    std::map< Handle, boost::shared_ptr< Source< int > > >* m_map;
};


/******INTERNAL FUNCTION DECLARATION******/

/******CLASS METHODS*******/
/*=====Listener=====*/
void Listener::Listen( std::vector< Handle >& read,
             std::vector< Handle >& write,
             std::vector< Handle >& exception)
{
    int read_count = read.size();
    int write_count = write.size();
    int excep_count = exception.size();
    
    struct timeval TIMEOUT = {7, 0};
    //set file descriptors into each of the fd sets
    fd_set* read_set = new fd_set[read_count];
    for (int i = 0; i < read_count; ++i)
    {
        FD_SET(i, read_set);
    }
    fd_set* write_set = new fd_set[write_count];
    for (int i = 0; i < write_count; ++i)
    {
        FD_SET(i, write_set);
    }
    fd_set* excep_set = new fd_set[excep_count];
    for (int i = 0; i < excep_count; ++i)
    {
        FD_SET(i, excep_set);
    }
    int max_fd = read_count > write_count ? read_count : write_count;
    max_fd = max_fd > excep_count ? max_fd : excep_count;

    //see which fds are active
    int activeEvents = select(max_fd + 1, read_set, write_set, excep_set, &TIMEOUT);

    if(0 > activeEvents)
    {
        std::cout << "Select Error" << std::endl;
    }
    else if(0 == activeEvents)
    {
        std::cout << "Listening Time out" << std::endl;
    }
    else
    {
        //add read to output
        read.clear();
        for (int fd = 0; fd < read_count; ++fd)
        {
            if(FD_ISSET(fd, read_set))
            {
                read.push_back(fd);
            }
        }
        //add write to output
        write.clear();
        for (int fd = 0; fd < write_count; ++fd)
        {
            if(FD_ISSET(fd, write_set))
            {
                write.push_back(fd);
            }
        }
        //add exception to output
        exception.clear();
        for (int fd = 0; fd < excep_count; ++fd)
        {
            if(FD_ISSET(fd, excep_set))
            {
                exception.push_back(fd);
            }
        }

    }
    delete[] read_set;
    delete[] write_set;
    delete[] excep_set;

}

/*=====Reactor=====*/
void Reactor::Add( MODE mode, Handle fd, Callback< Source< int > >* callback)
{
    assert(callback);

    boost::shared_ptr< Source< int > > newSrc = boost::make_shared< Source< int > >();
    newSrc->Subscribe(callback);
    
    switch(mode)
    {
        case (READ):
            m_read.insert(std::pair< Handle, boost::shared_ptr< Source< int > > >(fd, newSrc));
            break;
        case (WRITE):
            m_write.insert(std::pair< Handle, boost::shared_ptr< Source< int > > >(fd, newSrc));
            break;
        case (EXCEPTION):
            m_exception.insert(std::pair< Handle, boost::shared_ptr< Source< int > > >(fd, newSrc));
            break;
    }
}

void Reactor::Remove( MODE mode, Handle fd)
{   
    boost::shared_ptr< Source< int > > src;

    switch(mode)
    {
        case (READ):
            src = m_read.find(fd)->second;
            m_read.erase(m_read.find(fd));
            break;
        case (WRITE):
            src = m_write.find(fd)->second;
            m_write.erase(m_write.find(fd));
            break;
        case (EXCEPTION):
            src = m_exception.find(fd)->second;
            m_exception.erase(m_exception.find(fd));
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
        std::vector< Handle > readVector;
        std::for_each(m_read.begin(), 
                        m_read.end(),
                        PushToVector(&readVector));
        
        std::vector< Handle > writeVector;
        std::for_each(m_write.begin(), 
                        m_write.end(),
                        PushToVector(&writeVector));
        
        std::vector< Handle > exceptionVector;
        std::for_each(m_exception.begin(), 
                        m_exception.end(),
                        PushToVector(&exceptionVector));

        // call listener
        m_Listener.Listen(readVector, writeVector, exceptionVector);
        //run all active functions
        for_each(readVector.begin(), 
                readVector.end(), 
                CallNotify(&m_read));
        for_each(writeVector.begin(), 
                writeVector.end(), 
                CallNotify(&m_write));
        for_each(exceptionVector.begin(), 
                exceptionVector.end(), 
                CallNotify(&m_exception));
        
        readVector.clear();
        writeVector.clear();
        exceptionVector.clear();
    }
}

void Reactor::Stop()
{
    g_running = 0;
}

Reactor::~Reactor()
{

}

/*****FUNCTION DEFINITION******/
