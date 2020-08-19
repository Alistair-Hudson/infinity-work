/******************************************************************************
 *	Title:		Minion
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	09.08.2020.0
 ******************************************************************************/

#include "command.hpp"

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****STRUCTS*******/

/*****CLASSES******/

/*****FUNCTORS*****/

/******INTERNAL FUNCTION DECLARATION******/

/******CLASS METHODS*******/
/*===WRITE METHODS===*/
void ilrd::WriteCommand::operator()()
{
    int m_index = be64toh(m_params.m_request.m_index);
    memset((void*)&m_params.m_response, 0, m_params.m_response.ResponseSize());
    std::string msg;
    
    m_params.m_response.m_status =  m_params.m_storage.Write(m_index, (void*)m_params.m_request.m_data);
    switch(m_params.m_response.m_status)
    {
        case 0:
            msg += "Write to index ";
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

/*===READ METHODS===*/
void ilrd::ReadCommand::operator()()
{
    int m_index = be64toh(m_params.m_request.m_index);
    memset((void*)&m_params.m_response, 0, m_params.m_response.ResponseSize());
    std::string msg;
    
    m_params.m_response.m_status =  m_params.m_storage.Read(m_index, (void*)m_params.m_response.m_data);
    switch(m_params.m_response.m_status)
    {
        case 0:
            msg += "Write to index ";
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
/*****FUNCTION DEFINITION******/
/*===BUILDERS===*/
ilrd::BaseCommand* ilrd::WriteBuilder(Params m_params)
{
    return new WriteCommand(m_params);
    
}

ilrd::BaseCommand* ilrd::ReadBuilder(Params m_params)
{
    return new ReadCommand(m_params);
     
}