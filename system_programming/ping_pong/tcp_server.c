/******************************************************************************
 *	Title:		TCP Server
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	18.06.2020.0
 ******************************************************************************/
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))
#define MSGSIZE                 (100)
#define PORT                    (8080)

/******TYPEDEFS, GLOBAL VARIABLES******/

/******STRUCTS******/

/*****FUNCTIONS DECLARATIONS******/

/******FUNCTIONS******/ 
void func(int socket_id) 
{ 
    char buff[MSGSIZE]; 
    int character; 
    for (;;) { 
        bzero(buff, MSGSIZE); 
  
        read(socket_id, buff, sizeof(buff)); 
        printf("From client: %s\t To client : ", buff); 
        bzero(buff, MSGSIZE); 
        character = 0;
        while ((buff[character++] = getchar()) != '\n') 
            ; 
        write(socket_id, buff, sizeof(buff)); 
  
        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } 
    } 
} 

int main() 
{ 
    int socket_id;
    int connection_id;
    int length; 
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
   
    connection_id = accept(socket_id, (struct sockaddr*)&client_addr, &length); 
    if (connection_id < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
 
    func(connection_id); 
   
    close(socket_id); 
} 



