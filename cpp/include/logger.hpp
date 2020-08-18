#ifndef __ILRD_RD8586_LOGGER_HPP__
#define __ILRD_RD8586_LOGGER_HPP__

/*****************************************************************************
 * API Logger
 * Alistair Hudson
 * version 17.08.2020.0
******************************************************************************/

#include <stdlib.h> 

#include <iostream>
#include <string>
#include <boost/chrono.hpp>

#include "singleton.hpp"
#include "waitable.hpp"
#include "priority_que.hpp"

namespace ilrd
{

class Logger
{
public:
    enum ErrorLevel {
        ERROR = 0,
        WARNING,
        INFO,
        DEBUG
    };
    void PushMessage(ErrorLevel, std::string); // construct the message and push into the queue
    

private:

    struct Message
    {
        Message(ErrorLevel elevel = ERROR, std::string message = "ERROR"); // constructor computes time here

        inline bool operator>(const Message& other_) const
        {
            return (m_timepoint > other_.m_timepoint);
        }

        ErrorLevel m_error;
        std::string m_string;
        boost::chrono::system_clock::time_point m_timepoint;
    };

    friend class Singleton<Logger>;
    //thread which will take care of it 
    void PrintMessageIntoLogfile(); // print the message in the logfile with error level and timepoint
    Logger(); //: m_filename(getenv("LOGGERNAME"))
    //check creating is fine
    ~Logger();
    WaitableQueue<PriorityQueue<Message, std::vector<Message>, std::greater<Message> > , Message> m_wqueue;
    char * m_filename;
    bool m_run;
    boost::thread m_thread; // to set up in the constructor to run PrintMessageIntoLogfile
};

#define LOG_ERROR(msg) (Singleton<Logger>::GetInstance()->PushMessage(Logger::ERROR, (msg)))
#define LOG_WARNING(msg) (Singleton<Logger>::GetInstance()->PushMessage(Logger::WARNING, (msg)))
#define LOG_INFO(msg) (Singleton<Logger>::GetInstance()->PushMessage(Logger::INFO, (msg)))
#define LOG_DEBUG(msg) (Singleton<Logger>::GetInstance()->PushMessage(Logger::DEBUG, (msg)))

}

#endif /* __ILRD_RD8586_LOGGER_HPP__ */