/******************************************************************************
 *	Title:		UDP Connector
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	05.08.2020.0
 ******************************************************************************/
#include <iostream>

#include "udp_connector.hpp"

/******MACROS******/
#define PORT (8080)

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****STRUCTS*******/

/*****CLASSES******/

/*****FUNCTORS*****/

/******INTERNAL FUNCTION DECLARATION******/


/******CLASS METHODS*******/
/*=====UDPConnector=====*/
ilrd::UDPConnector::UDPConnector(int port)
{
     

    if ( (m_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        throw "socket creation failed\n"; 
    }

    m_server_addr.sin_family = AF_INET; 
    m_server_addr.sin_addr.s_addr = INADDR_ANY; 
    m_server_addr.sin_port = htons(port);

    if (bind(m_socket, (struct sockaddr*)&m_server_addr, sizeof(m_server_addr)) < 0)
    {
        throw "Connection failed\n";
    } 
}

ilrd::UDPConnector::~UDPConnector()
{
    close(m_socket);
}

/*****FUNCTION DEFINITION******/
 