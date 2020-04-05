
#ifndef __OL85_DHCP_H__
#define __OL85_DHCP_H__

/*******************************************************************************
                                * OL85 API FOR DHCP
                                * version 29.03.2020.0
*******************************************************************************/
#include <stddef.h>	/* size_t */
enum child_t
{
    ZERO,
    ONE,
    NUM_OF_CHILDREN
};

typedef enum status
{
    SUCCESS,
	SYSTEM_FAIL,
	SUB_NET_FULL
} DHCP_status_t;

#define CHARIP_SIZE     (4)

typedef unsigned char ip_t[CHARIP_SIZE];

typedef struct dhcp dhcp_t;

typedef struct trie_node trie_node_t;

/*******************************************************************************
*Input: ip_t address to the network, and the number of bits of the subnet
*Process:
* - The following addresses are reserve:
    0.0.0.0
    255.255.255.255 for broadcast
    255.255.255.254 for server
*Return: dhcp_t struct that contains pointer to the root, ip_t network, and
*number of bits at the subnet.
*******************************************************************************/
dhcp_t *DHCPCreate(ip_t network, size_t subnet_num_of_bits);

/*******************************************************************************
*Input: pointer to dhcp_t struct
*Process: free the dhcp_t struct
*******************************************************************************/
void DHCPDestroy(dhcp_t *dhcp);

/*******************************************************************************
*Input: pointer to dhcp_t struct, a propose_address to be allocated, the final
* address where the address will be allocated.
*Process: The program will look it the propose_address is free and allocated an
* address with this Ip. If the propose_address occupied, the following closet
* address will be use.
* Return: DHCP_status_t can be:
                                SUCCESS,
                                SYSTEM_FAIL,
                                SUB_NET_FULL,
*******************************************************************************/
DHCP_status_t DHCPAllocate(dhcp_t *dhcp, ip_t propose_addr, ip_t return_addr);

/*******************************************************************************
*Input: pointer to dhcp_t struct and the Ip address (key) to be free
*Process: free the location of the given ip address
*******************************************************************************/
void DHCPFree(dhcp_t *dhcp, ip_t key);

/*******************************************************************************
*Input: pointer to dhcp_t struct
*Process: Calculate the number of free IPs available for allocation
*Return: number of free IPs available for allocation
*******************************************************************************/
size_t CountFree(dhcp_t *dhcp);

#endif /* __OL85_DHCP_H__ */
