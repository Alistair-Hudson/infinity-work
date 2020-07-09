#include <sys/socket.h> 
#include <sys/types.h>
#include <netdb.h> 
#include <netinet/in.h> 

#include "reactor.hpp"

#define PORT (8080)

class TestListen: public IListener
{
public:
    TestListen(){}
    //std::vector<HandleAndMode> Listen(const std::vector<HandleAndMode>& handle){}
private:
};


void TestFoo(int fd)
{
    std::cout << "Foo activated" << std::endl;
}

void TestBar(int fd)
{
    std::cout << "Bar activated" << std::endl;
}

int main()
{
    //TestListen listen();
    Reactor reactor(new TestListen);

     int socket_id;
    int connection_id;
    unsigned int length; 
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr; 
  
    socket_id = socket(AF_INET, SOCK_STREAM, 0); 
    if (socket_id == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    
    bzero(&server_addr, sizeof(server_addr)); 

    server_addr.sin_family = AF_INET; 
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    server_addr.sin_port = htons(PORT); 
  
    if ((bind(socket_id, (struct sockaddr*)&server_addr, sizeof(server_addr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 

    if ((listen(socket_id, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 

    length = sizeof(client_addr); 
   
    connection_id = accept(socket_id, NULL, 0); 
    if (connection_id < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 

    reactor.Add(std::make_pair(READ, socket_id), TestFoo);
    reactor.Add(std::make_pair(READ, connection_id), TestBar);

    reactor.Run();

    return 0;
}