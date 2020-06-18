/******************************************************************************
 *	Title:		UDP Server
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	18.06.2020.0
 ******************************************************************************/
#include <stdlib.h>		/*  */
#include <assert.h>		/* assert */
#include <string.h>		/* strcpy */
#include <stdio.h>		/* printf */
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))
#define MSGSIZE                 (100)
#define PORT                    (8080)

/******TYPEDEFS, GLOBAL VARIABLES******/

/******STRUCTS******/

/*****FUNCTIONS DECLARATIONS******/

/******FUNCTIONS******/
int main() { 
    int socket_id;
    int length;
    int bytes_received;
    char buffer[MSGSIZE]; 
    char *message = "ping"; 
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr; 
    
    if ( (socket_id = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&server_addr, 0, sizeof(server_addr)); 
    memset(&client_addr, 0, sizeof(client_addr)); 
    
    server_addr.sin_family    = AF_INET; 
    server_addr.sin_addr.s_addr = INADDR_ANY; 
    server_addr.sin_port = htons(PORT); 
     
    if ( bind(socket_id, (const struct sockaddr *)&server_addr,  
            sizeof(server_addr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    }  
  
    length = sizeof(client_addr);  //length is value/resuslt 
  
    bytes_received = recvfrom(socket_id, (char *)buffer, MSGSIZE,  
                MSG_WAITALL, ( struct sockaddr *) &client_addr, 
                &length); 
    buffer[bytes_received] = '\0'; 
    printf("Client : %s\n", buffer); 
    sendto(socket_id, (const char *)message, strlen(message),  
        MSG_CONFIRM, (const struct sockaddr *) &client_addr, 
            length);  
      
    return 0; 
}



