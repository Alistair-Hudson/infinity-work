#include <sys/socket.h> 
#include <sys/types.h>
#include <netdb.h> 
#include <netinet/in.h> 

#include "reactor_w_callback.hpp"

#define PORT (8080)

/****GLOBAL VARIABLES****/

Reactor reactor;

/****FUNCTORS*****/

/****ClASSES*****/

/******FUNCTIONS****/
void TestFoo(int);
void TestBar(int);

void TestFoo(int fd)
{
    std::cout << "Foo activated" << std::endl;
    int connection_id = accept(fd, NULL, 0); 
    if (connection_id < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    }
 /*   Callback<Source<int>> newCB(TestBar);
    reactor.Add(READ, connection_id, &newCB);
*/}

void TestBar(int fd)
{
    std::cout << "Bar activated" << std::endl;
}

int main()
{
    //TestListen listen();
    

    int socket_id;
    int connection_id;
    unsigned int length; 
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr; 

    Callback<Source<int>>::CallbackPointer FooNotify(TestFoo);
    Callback<Source<int>> callback1(FooNotify);
  
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
   


    reactor.Add(READ, socket_id, &callback1);
    

    reactor.Run();

    return 0;
}