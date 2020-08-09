#ifndef ILRD_RD8586_UDP_CONNECTOR_HPP
#define ILRD_RD8586_UDP_CONNECTOR_HPP
/*****************************************************************************
 * API UDP Connector
 * Alistair Hudson
 * version 05.08.2020.0
******************************************************************************/
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 

#include "boost/core/noncopyable.hpp"

#define PORT    (8080)

namespace ilrd
{

class UDPConnector: private boost::noncopyable
{
public:
    explicit UDPConnector(int port = PORT);
    ~UDPConnector();

    inline int GetFD() const {return m_socket;}
    inline struct sockaddr_in* GetServerAdd() {return &m_server_addr;}

private:
    int m_socket;
    struct sockaddr_in m_server_addr;
};

} // namespace ilrd

#endif // ILRD_RD8586_UDP_CONNECTOR_HPP  