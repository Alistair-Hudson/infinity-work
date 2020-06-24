/******************************************************************************
 *	Title:		TCP-UDP Server
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	24.06.2020.0
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
#include <netdb.h> 
#include <netinet/in.h> 
#include <sys/select.h> /* select, FD Macros */

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))
#define MSGSIZE                 (100)
#define TCP_PORT                (8080)
#define UDP_PORT                (8081)
#define BROADCAST_PORT          (8082)

/******TYPEDEFS*****/

/******GLOBAL VARIABLES******/
static int nfds = 1;
struct timeval TIMEOUT = {7};

/******STRUCTS******/

/*****FUNCTIONS DECLARATIONS******/
int SetSocket(struct sockaddr_in* server, size_t server_size, fd_set* set, int port);

/******FUNCTIONS******/
//Server
int main()
{
    fd_set listening_list;
    fd_set client_list;

    int tcp_socket_id;
    int udp_socket_id;
    int udp_broadcast_id;

    struct sockaddr_in tcp_server;
    struct sockaddr_in udp_server;
    struct sockaddr_in broadcast_server;

    //create fds set list
    FD_ZERO(&listening_list);
    FD_ZERO(&client_list);

    //create TCP server listener socket
    if (0 > (tcp_socket_id = SetSocket(&tcp_server, sizeof(tcp_server), &listening_list, TCP_PORT)))
    {
        return 1;
    }
    printf("tcp = %d\n", tcp_socket_id);
    //create UDP server listener socket
    if (0 > (udp_socket_id = SetSocket(&udp_server, sizeof(udp_server), &listening_list, UDP_PORT)))
    {
        return 1;
    }
    printf("udp = %d\n", udp_socket_id);
    //create UDP broadcast server listener socket
    if (0 > (udp_broadcast_id = SetSocket(&broadcast_server, sizeof(broadcast_server), &listening_list, BROADCAST_PORT)))
    {
        return 1;
    }
    printf("broadcast = %d\n", udp_broadcast_id);
    //initialize with all previous sockets

    while(1)
    {
        int i = 0;
        int fd = select(nfds, &listening_list, NULL, NULL, &TIMEOUT);
        if (0 == fd)
        {
            printf("Listen timed out\n");
        }
        printf("%d\n", fd);/*
        for (i = 0; i <= nfds, ++i)
        {
            if (FD_ISSET(fd, listening_list))
            {
                if (fd == tcp_socket_id)
                {
                    int new_fd = accept(fd, NULL, 0);
                    FD_SET(new_fd, listening_list);
                    FD_SET(new_fd, client_list);
                    //read
                    //respond
                }
                if (fd == udp_socket_id)
                {
                    //Recieve
                    //Send
                }
                if (fd == udp_broadcast_id)
                {
                    //Recieve
                    //Send
                }
                if (fd == stdin)
                {
                    //read from fd//scanf
                    //write to stdout//printf
                }
                if (FD_ISSET(fd, client_list))
                {
                    //read
                    //respond
                }
            }
        }*/
    }

    return 0;
}

int SetSocket(struct sockaddr_in* server, size_t server_size, fd_set* set, int port)
{
    int socket_id = socket(AF_INET, SOCK_STREAM, 0); 
    if (socket_id == -1) 
    { 
        perror("socket creation failed: "); 
        return -1; 
    }
    server->sin_family = AF_INET; 
    server->sin_addr.s_addr = htonl(INADDR_ANY); 
    server->sin_port = htons(port); 
  
    if ((bind(socket_id, (struct sockaddr*)server, server_size)) != 0) 
    { 
        perror("socket bind failed: "); 
        return -1; 
    } 

    if ((listen(socket_id, 5)) != 0) 
    { 
        perror("Listen failed: "); 
        return -1; 
    } 
    FD_SET(socket_id, set);
    ++nfds;

    return socket_id;
}