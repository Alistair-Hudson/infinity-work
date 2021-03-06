/******************************************************************************
 *	Title:		UDP Client
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
#define PORT                    (8081)

/******TYPEDEFS, GLOBAL VARIABLES******/

/******STRUCTS******/

/*****FUNCTIONS DECLARATIONS******/

/******FUNCTIONS******/
int main() { 
    int socket_id;
    int length;
    int bytes_received;
    char buffer[MSGSIZE]; 
    char *message = "pong"; 
    struct sockaddr_in server_addr; 
    
    if ( (socket_id = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&server_addr, 0, sizeof(server_addr));  
    
    server_addr.sin_family = AF_INET; 
    server_addr.sin_addr.s_addr = INADDR_ANY; 
    server_addr.sin_port = htons(PORT); 
     
    /*if ( bind(socket_id, (const struct sockaddr *)&server_addr,  
            sizeof(server_addr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    }  */
  
    sendto(socket_id, (const char *)message, strlen(message),  
        MSG_CONFIRM, (const struct sockaddr *) &server_addr, 
            sizeof(server_addr));  
  
    bytes_received = recvfrom(socket_id, (char *)buffer, MSGSIZE,  
                MSG_WAITALL, ( struct sockaddr *) &server_addr, 
                &length); 
    buffer[bytes_received] = '\0'; 
    printf("Server : %s\n", buffer); 
    
    close(socket_id);  
    return 0; 
}  
