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
#define MSGSIZE                 (50)
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

    int tcp_socket_id = 0;
    int udp_socket_id = 0;
    int udp_broadcast_id = 0;
    int lowest_socket = 0;

    struct sockaddr_in tcp_server;
    struct sockaddr_in udp_server;
    struct sockaddr_in broadcast_server;
    struct sockaddr_in client_addr;

    //create fds set list
    FD_ZERO(&listening_list);
    FD_ZERO(&client_list);

    //create TCP server listener socket
    if (0 > (tcp_socket_id = SetSocket(&tcp_server, sizeof(tcp_server), &listening_list, TCP_PORT)))
    {
        return 1;
    }
    lowest_socket = tcp_socket_id;
    printf("tcp = %d\n", tcp_socket_id);
    //create UDP server listener socket
    if (0 > (udp_socket_id = SetSocket(&udp_server, sizeof(udp_server), &listening_list, UDP_PORT)))
    {
        return 1;
    }
    if (lowest_socket > udp_socket_id)
    {
        lowest_socket = udp_socket_id;
    }
    printf("udp = %d\n", udp_socket_id);
    //create UDP broadcast server listener socket
    if (0 > (udp_broadcast_id = SetSocket(&broadcast_server, sizeof(broadcast_server), &listening_list, BROADCAST_PORT)))
    {
        return 1;
    }
    if (lowest_socket > udp_broadcast_id)
    {
        lowest_socket = udp_broadcast_id;
    }
    printf("broadcast = %d\n", udp_broadcast_id);
    //initialize with all previous sockets

    while(1)
    {
        int fd = 0;
        int number_of_fds = select(nfds, &listening_list, NULL, NULL, &TIMEOUT);
        /*if (0 == number_of_fds)
        {
            printf("Listen timed out\n");
        }*/
        for (fd = lowest_socket; fd < nfds+lowest_socket; ++fd)
        {
            if (FD_ISSET(fd, &listening_list))
            {
                if (fd == tcp_socket_id)
                {
                    char buffer[MSGSIZE];
                    int new_fd = accept(fd, NULL, 0);
                    FD_SET(new_fd, &listening_list);
                    FD_SET(new_fd, &client_list);
                    ++nfds;
                    //read
                    read(new_fd, buffer, sizeof(buffer));
                    
                    //respond
                    write(new_fd, "new pong\n", sizeof(buffer));

                }
                if (fd == udp_socket_id)
                {
                    char buffer[MSGSIZE];
                    int bytes_received = 0;
                    //Recieve
                    bytes_received = recvfrom(fd, buffer, MSGSIZE, 
                                                MSG_WAITALL, (struct sockaddr*)&client_addr,
                                                (int*)sizeof(client_addr));
                    buffer[bytes_received] = '\0';
                    //Send
                    sendto(fd, "pomg\n", MSGSIZE, 
                            MSG_CONFIRM, (struct sockaddr*)&client_addr, 
                            sizeof(client_addr));
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
                if (FD_ISSET(fd, &client_list))
                {
                    char buffer[50];
                    //read
                    read(fd, buffer, sizeof(buffer));
                    
                    //respond
                    write(fd, "old pong\n", sizeof(buffer));
                }
            }
        }
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