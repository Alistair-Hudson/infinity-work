/*******************************************************************************
                                 * DHCP * 
*******************************************************************************/
#include "dhcp.h"	/* size_t */
#include <stdlib.h>
#include <stdio.h>
/*enum child_t TODO this is an issue on my end
{
    ZERO,
    ONE,
    NUM_OF_CHILDREN
};

typedef struct trie_node
{
    struct trie_node *children[NUM_OF_CHILDREN];
    int is_full;
} trie_node_t; TODO you redefined here, trie_node_t is defined in the .h file
*/
struct dhcp
{
    ip_t network;
    size_t height;
    trie_node_t *root;
};
/******************************************************************************/
#define SIZE_IP (32)
#define RESERVED (3)

void Destroy                        (trie_node_t *node);
int NoPropose                       (ip_t propose_addr);
size_t  LeafCount                   (trie_node_t *node);
static void PrintBitArr             (int bitarr);

static trie_node_t *CreateNode      (void);
static int IsFULL                   (trie_node_t *node);
static int IsExist                  (trie_node_t * node);
static int IsNextWasZero            (int path, size_t height);

static void CopyIP                  (unsigned char* source, unsigned char* dest);
static int ConvertToBitarr          (dhcp_t *server, ip_t ip);
static void ConvertToIP             (dhcp_t *server, int path , ip_t ip);
static int IsFullFamily             (trie_node_t*node);

static void ReverseStr              (unsigned char* str, size_t size);
static void SwapChar                (unsigned char *ch1, unsigned char*ch2);

static int SubRemove                (int path,size_t height ,trie_node_t *node);
static DHCP_status_t FillReservedIP (dhcp_t * dhcp);
DHCP_status_t  IPPath               (trie_node_t **node, int *path,size_t height);

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
dhcp_t *DHCPCreate(ip_t network, size_t subnet_num_of_bits)
{
    dhcp_t *server = malloc(sizeof(dhcp_t));
    if (NULL == server)
    {
        return NULL;
    }

    server->root = CreateNode();
    if(NULL == server->root)
    {
        free(server->root);
        server->root = NULL;
        
        return NULL;
    }

    CopyIP((unsigned char*)network, (unsigned char*)server->network);
    server->height = SIZE_IP - subnet_num_of_bits;
    
    if (SYSTEM_FAIL == FillReservedIP(server))
    {
        DHCPDestroy(server);
        return NULL;
    }

    return server;
}
/*******************************************************************************
*Input: pointer to dhcp_t struct
*Process: free the dhcp_t struct
*******************************************************************************/
void DHCPDestroy(dhcp_t *dhcp)
{
    Destroy(dhcp->root);
    
    free(dhcp);
    dhcp = NULL;
}

void Destroy(trie_node_t *node)
{
    if (NULL == node)
    {
        return;
    }
    
    Destroy(node->children[ZERO]);
    Destroy(node->children[ONE]);
    
    free(node);
    node = NULL;
}

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

DHCP_status_t DHCPAllocate(dhcp_t *dhcp, ip_t propose_addr, ip_t return_addr)
{
    DHCP_status_t status = SUCCESS;
    size_t size = CountFree(dhcp);
    int path = 0;
    
    if (size == 0)
    {
        return SUB_NET_FULL;
    }

    path = ConvertToBitarr(dhcp,propose_addr);

    status = IPPath(&(dhcp->root),&path ,dhcp->height);
    
    ConvertToIP(dhcp, path, return_addr);

    return status; 
}

DHCP_status_t  IPPath(trie_node_t **node, int *path, size_t height)
{/*TODO warning reaches end of non-void, see if you can remake the if/else
	into a way where when all else fails return*/
    int side = IsOn(*path, height-1);
    int returned_path = *path;
    DHCP_status_t status = SUCCESS; 

    if (!IsExist(*node))
    {
        *node = CreateNode();
        if (!IsExist(*node))
        {
           return SYSTEM_FAIL; 
        }

        if (0 == height && !IsFULL(*node))
        {
            (*node)->is_full = 1;
            return SUCCESS;
        }

        status = SUCCESS;
    }
    if (IsFULL(*node))
    {
        return  PROPOSE_FULL;/*TODO what is this, not in the .h file*/
    }

    if (SUCCESS == (status = IPPath(&((*node)->children[side]), path, height-1)))
    {
       if( IsFullFamily(*node))
        {
            (*node)->is_full = 1;
        }

        return status;
    }
    else if (!IsNextWasZero(*path, height))
    {
        return PROPOSE_FULL;
    }
    else 
    {
        while(!IsOn(*path, height-1))
        {
            (*path)+=1;
        }
        
        status = IPPath(&((*node)->children[IsOn(*path, height-1)]), path, height-1);
        if (status == SUCCESS)
        {
            if( IsFullFamily(*node))
            {
                (*node)->is_full = 1;
            }
        }
       
        return status; 
    }
   
}

/******************************************************************************/
int IsOn(int bits_array, int index)
{
    return (0 !=(bits_array &(1 << index)));
}

static int IsFULL(trie_node_t *node)
{
    return (node->is_full);
}

static int IsExist(trie_node_t * node)
{
    return NULL != node;
}

static int IsNextWasZero(int path, size_t height)
{
    return !IsOn(path, height -1);
}

/*******************************************************************************
*Input: pointer to dhcp_t struct and the Ip address (key) to be free
*Process: free the location of the given ip address
*******************************************************************************/
void DHCPFree(dhcp_t *dhcp, ip_t key)
{
    int path = ConvertToBitarr(dhcp,key);

    SubRemove(path,dhcp->height ,dhcp->root);

}
static int SubRemove(int path,size_t height ,trie_node_t *node)
{
    int side = 0;
    int status = 0;

    if(NULL == node)
    {
        return -1;
    }

    if (height == 0)
    {
        free(node);
        node = NULL;

        return 0;
    }

    side = IsOn(path, height-1);

   if (-1 != (status = SubRemove(path, height-1, node->children[side])))
   {
        node->children[side] = NULL;

        if (node->children[0] == NULL &&
            node->children[1] == NULL)
        {
            free(node);
            node = NULL;
        }
        else
        {
            status = -1;
        }
   }

   return status;
}
/*******************************************************************************
*Input: pointer to dhcp_t struct
*Process: Calculate the number of free IPs available for allocation
*Return: number of free IPs available for allocation
*******************************************************************************/
size_t CountFree(dhcp_t *dhcp)/*TODO conflicting type, maybe  an issue on my end*/
{
    trie_node_t *node = dhcp->root;
    size_t full_trie = 1 << (dhcp->height);
    size_t Leaves = 0;

    Leaves = LeafCount(node);
    return(full_trie - Leaves);
}
size_t  LeafCount(trie_node_t *node)  
{  
    if (NULL == node)
    {
        return 0;
    }

    if(NULL == node->children[ZERO] && NULL == node->children[ONE]) 
    {
        return 1;          
    } 
        
    return LeafCount(node->children[ZERO])+  
            LeafCount(node->children[ONE]);  
}  
  
/*******************************************************************************/

static DHCP_status_t FillReservedIP(dhcp_t * dhcp)
{
    ip_t broadcast = {255,255,255,255};
    ip_t network = {255,255,255,254};
    ip_t server = {0,0,0,0};
    ip_t return_addr = {0};
    DHCP_status_t status = SUCCESS;

    if (SYSTEM_FAIL == (status = DHCPAllocate(dhcp, network, return_addr)))
    {
        DHCPDestroy(dhcp);
        return status;
    } 
    
    if (SYSTEM_FAIL == (status = DHCPAllocate(dhcp, broadcast, return_addr)))
    {
        DHCPDestroy(dhcp);
        return status;
    }
    
    if (SYSTEM_FAIL == (status = DHCPAllocate(dhcp, server, return_addr)))
    {
        DHCPDestroy(dhcp);
        return status; 
    }
    
    status = SUCCESS;
    return status;
}

static trie_node_t *CreateNode()
{
    trie_node_t *node = malloc(sizeof(trie_node_t));
    if(NULL == node)
    {
        return NULL;
    }
    node->is_full = 0;
    node->children[ZERO] = NULL;
    node->children[ONE] = NULL;

    return node;
}
/*******************************************************************************/
#define SIZE_CHAR (8)
/* return bitarr last bit is the start of tries */
static int ConvertToBitarr(dhcp_t *server, ip_t ip)/*TODO server unused*/
{
    int result  = 0;
    
    ReverseStr(ip,4); 
    result = *(int *)ip;
    
    return result;
}

static void ConvertToIP(dhcp_t *server, int path , ip_t ip)/*TODO server unused*/
{
    unsigned char *to_ip = NULL;
  
    to_ip = ((unsigned char*)&path);
    CopyIP(to_ip, (unsigned char*)ip);
}

static void ReverseStr(unsigned char* str, size_t size)
{
    unsigned char *start = (unsigned char *)str;
    unsigned char *end = (unsigned char *)str + size - 1;

    while(start < end)
    {
        SwapChar(start, end);
        start++;
        end--;
    } 
}

static void SwapChar(unsigned char *ch1, unsigned char*ch2)
{
    unsigned char tmp = *ch1;
    *ch1 = *ch2;
    *ch2 = tmp;
}

static void CopyIP(unsigned char* source, unsigned char* dest)
{
  size_t i = 0;

  for (i = 0; i < 4; i++)
  {
    dest[i] = source[i];
  }
}

static int IsFullFamily(trie_node_t*node)
{
    if((node->children[ZERO]==NULL && node->children[ONE] !=NULL) ||
        (node->children[ONE]==NULL && node->children[ZERO] !=NULL ))
    {
        return 0;
    }
    return ((node->children[ZERO]== NULL && node->children[ONE] ==NULL)||
            (IsFULL(node->children[ZERO]) && IsFULL(node->children[ONE])));
}
