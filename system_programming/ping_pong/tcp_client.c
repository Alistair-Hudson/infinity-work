/******************************************************************************
 *	Title:		TCO Client
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	18.06.2020.0
 ******************************************************************************/
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 

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
        bzero(buff, sizeof(buff)); 
        printf("Enter the string : "); 
        character = 0; 
        while ((buff[character++] = getchar()) != '\n') 
            ; 
        if ((strncmp(buff, "exit", 4)) == 0) { 
        printf("Client Exit...\n"); 
        break; 
        }
        else
        {         
        write(socket_id, buff, sizeof(buff)); 
        bzero(buff, sizeof(buff)); 
        read(socket_id, buff, sizeof(buff)); 
        printf("From Server : %s", buff); 
        if ((strncmp(buff, "exit", 4)) == 0) { 
            printf("Client Exit...\n"); 
            break; 
        }
        } 
    } 
} 
  
int main() 
{ 
    int socket_id;
    int connection_id; 
    struct sockaddr_in sever_addr;
    struct sockaddr_in client_addr; 
  
    socket_id = socket(AF_INET, SOCK_STREAM, 0); 
    if (socket_id == -1) { 
        printf("socket creation failed...\n"); 
        return (0); 
    } 
  
    bzero(&sever_addr, sizeof(sever_addr)); 

    sever_addr.sin_family = AF_INET; 
    sever_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    sever_addr.sin_port = htons(PORT); 
  
    if (connect(socket_id, (struct sockaddr*)&sever_addr, sizeof(sever_addr)) != 0) { 
        printf("connection with the server failed...\n"); 
        return (0); 
    } 
    func(socket_id); 

    close(socket_id); 
} 