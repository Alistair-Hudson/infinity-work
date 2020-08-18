/******************************************************************************
 *	Title:		Logger
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	17.08.2020.0
 ******************************************************************************/
#include <fstream>

#include "logger.hpp"

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****STRUCTS*******/

/*****CLASSES******/

/*****FUNCTORS*****/

/******INTERNAL FUNCTION DECLARATION******/

/******CLASS METHODS*******/
/*===Logger===*/
ilrd::Logger::Logger(): m_filename(getenv("LOGGERNAME")),
                        m_run(1),
                        m_thread(boost::bind(&Logger::PrintMessageIntoLogfile, this))
{

}

ilrd::Logger::~Logger()
{
    m_run = 0;
    PushMessage(INFO, "END OF LOG");
    m_thread.join();
}

void ilrd::Logger::PushMessage(ErrorLevel elevel, std::string message)
{
    Message msg(elevel, message);
    m_wqueue.Push(msg);

}

void ilrd::Logger::PrintMessageIntoLogfile()
{

    std::fstream fs;
    fs.open(m_filename, std::ios::app);

    while(m_run)
    {
        Message msg;
        m_wqueue.Pop(msg);
        std::time_t t = boost::chrono::system_clock::to_time_t(msg.m_timepoint);
        fs  << std::ctime(&t) << "\t";
        
        switch(msg.m_error)
        {
            case ERROR:
                fs << "ERROR, ";
                break;
            case WARNING:
                fs << "WARNING, ";
                break;
            case INFO:
                fs << "INFO, ";
                break;
            case DEBUG:
                fs << "DEBUG, ";
                break;
            default:
                break;
        }

        fs << msg.m_string << std::endl;
    }
    fs.close();
    
}

/*==Logger::Message===*/
ilrd::Logger::Message::Message(ErrorLevel elevel, std::string message): m_error(elevel),
                                                                        m_string(message)
{
    m_timepoint = boost::chrono::system_clock::now();
}


/*****FUNCTION DEFINITION******/
 