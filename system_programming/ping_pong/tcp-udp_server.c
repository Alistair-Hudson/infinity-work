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
struct timeval TIMEOUT = {7, 0};

/******STRUCTS******/

/*****FUNCTIONS DECLARATIONS******/
int SetSocket(struct sockaddr_in* server, size_t server_size, fd_set* set, int port, int packet_type);

/******FUNCTIONS******/
//Server
int main()
{
    fd_set listening_list;
    fd_set client_list;

    int tcp_socket_id = 0;
    int udp_socket_id = 0;
    int udp_broadcast_id = 0;
    int run = 1;
    int broadcast = 1;

    struct sockaddr_in tcp_server;
    struct sockaddr_in udp_server;
    struct sockaddr_in broadcast_server;
    struct sockaddr_in client_addr;

    //create fds set list
    FD_ZERO(&listening_list);
    FD_ZERO(&client_list);

    FD_SET(0, &listening_list);//set to listen to stdin
    ++nfds;

    //create TCP server listener socket
    if (0 > (tcp_socket_id = SetSocket(&tcp_server, sizeof(tcp_server), &listening_list, TCP_PORT, SOCK_STREAM)))
    {
        return 1;
    }
    if ((listen(tcp_socket_id, 5)) != 0) 
    { 
        perror("Listen failed: "); 
        return -1; 
    } 

    //create UDP server listener socket
    if (0 > (udp_socket_id = SetSocket(&udp_server, sizeof(udp_server), &listening_list, UDP_PORT, SOCK_DGRAM)))
    {
        return 1;
    }

    //create UDP broadcast server listener socket
    if (0 > (udp_broadcast_id = SetSocket(&broadcast_server, sizeof(broadcast_server), &listening_list, BROADCAST_PORT, SOCK_DGRAM)))
    {
        return 1;
    }
    if(setsockopt(udp_broadcast_id, SOL_SOCKET, SO_BROADCAST, 
                    &broadcast, sizeof(broadcast)));
    //initialize with all previous sockets
    while(run)
    {
        int fd = 0;
        int number_of_fds = select(nfds+1, &listening_list, NULL, NULL, &TIMEOUT);
        if (0 == number_of_fds)
        {
            printf("Listen timed out\n");
        }
        for (fd = 0; fd <= nfds; ++fd)
        {
            if (FD_ISSET(fd, &listening_list))
            {
                
                if (fd == tcp_socket_id)
                {
                    char buffer[MSGSIZE];
                    int new_fd = accept(fd, NULL, 0);
                    if (0 > new_fd)
                    {
                        perror("Socket acception failed: ");
                    }
                    bzero(buffer, MSGSIZE);
                    FD_SET(new_fd, &listening_list);
                    FD_SET(new_fd, &client_list);
                    nfds = nfds < new_fd ? new_fd : nfds;
                    //read
                    read(new_fd, buffer, sizeof(buffer));
                    
                    //respond
                    write(new_fd, "new pong\n", sizeof(buffer));

                }
                if (fd == udp_socket_id)
                {
                    char buffer[MSGSIZE];
                    int bytes_received = 0;
                    int length = sizeof(client_addr);
                    char message[] = "udp pong\n";
                    //Recieve
                    bytes_received = recvfrom(fd, (char*)buffer, MSGSIZE, 
                                                MSG_WAITALL, (struct sockaddr*)&client_addr,
                                                &length);
                    buffer[bytes_received] = '\0';
                    //Send
                    sendto(fd, (const char*)message, strlen(message), 
                            MSG_CONFIRM, (struct sockaddr*)&client_addr, 
                            length);
                }
                if (fd == udp_broadcast_id)
                {
                    char buffer[MSGSIZE];
                    int bytes_received = 0;
                    int length = sizeof(client_addr);
                    char message[] = "broadcast pong\n";
                    //Recieve
                    bytes_received = recvfrom(fd, (char*)buffer, MSGSIZE, 
                                                MSG_WAITALL, (struct sockaddr*)&client_addr,
                                                &length);
                    buffer[bytes_received] = '\0';
                    //Send
                    sendto(fd, (const char*)message, strlen(message), 
                            MSG_CONFIRM, (struct sockaddr*)&client_addr, 
                            length);
                }
                if (0 == fd)
                {
                    char buffer[MSGSIZE];
                    //read from fd//scanf
                    scanf("%s", buffer);
                    if(!strcmp(buffer, "ping"))
                    {
                        //write to stdout//printf
                        printf("pong\n");
                    }
                    if (!strcmp(buffer, "quit"))
                    {
                        run = 0;
                    }
                }
                if (FD_ISSET(fd, &client_list))
                {
                    char buffer[MSGSIZE];
                    bzero(buffer, MSGSIZE);
                    //read
                    if (!read(fd, buffer, sizeof(buffer)))
                    {
                        printf("client %d lost\n", fd);
                        FD_CLEAR(fd, &client_list);
                        close(fd);
                    }
                    //respond
                    write(fd, "old pong\n", sizeof(buffer));
                }
            }
            FD_SET(fd, &listening_list);
        }
        TIMEOUT.tv_sec = 7;
    }

    for(int socket = 0; socket <= nfds; ++socket)
    {
        close(socket);
    }
    return 0;
}

int SetSocket(struct sockaddr_in* server, size_t server_size, fd_set* set, int port, int packet_type)
{
    int socket_id = socket(AF_INET, packet_type, 0); 
    if (socket_id == -1) 
    { 
        perror("socket creation failed: "); 
        return -1; 
    }
    server->sin_family = AF_INET; 
    server->sin_addr.s_addr = htonl(INADDR_ANY); 
    server->sin_port = htons(port); 
  
    if ((bind(socket_id, (const struct sockaddr*)server, server_size)) != 0) 
    { 
        perror("socket bind failed: "); 
        return -1; 
    } 

    FD_SET(socket_id, set);
    nfds = nfds < socket_id ? socket_id : nfds;

    return socket_id;
}