/******************************************************************************
 *	Title:		DHCP
 *	Authour:	Alistair Hudson
 *	Reviewer:	Shmuel
 *	Version:	01.04.2020.0
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>		/* assert */

#include "dhcp.h"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))
#define MAX_BITS				(31) /*The 0th bit is included in this number*/
#define FULL_MASK				(0xFFFFFFFF)
#define BIT_MASK				(1)
#define BYTE_SHIFT				(8)
#define CHAR_MAX				(255)

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
struct dhcp
{
    ip_t network;
    size_t subnet_num_of_bits;
    trie_node_t *root;
};

struct trie_node
{
    trie_node_t* children[NUM_OF_CHILDREN];
    int is_full;
};

static ip_t network_add = {0, 0, 0, 0};

static ip_t broadcast_add = {255, 255, 255, 255};

static ip_t server_add = {255, 255, 255, 254};


static DHCP_status_t AllocateImp(trie_node_t* node, size_t address, size_t shift);

static DHCP_status_t IsFreeAddress(trie_node_t* node, size_t address, size_t shift);

static trie_node_t* CreateNode(void);

static void CopyAddress(ip_t src, ip_t des);

static void FreeImp(trie_node_t* node, size_t address, size_t shift);

static size_t CountSupport(trie_node_t* node, size_t level);

static void DestroySupport(trie_node_t* node);

static size_t ConvertAddress(ip_t address);

static void IncrementReturn(ip_t return_addr, int index);

/******FUNCTIONS******/
dhcp_t *DHCPCreate(ip_t network, size_t subnet_num_of_bits)
{
	size_t MASK = 0;

	dhcp_t* new_dhcp = malloc(sizeof(struct dhcp));
	if(NULL == new_dhcp)
	{
		return NULL;
	}
	CopyAddress(network, new_dhcp->network);
	new_dhcp->subnet_num_of_bits = subnet_num_of_bits;

	new_dhcp->root = CreateNode();/*TODO*/
	if (NULL == new_dhcp->root)
	{
		free(new_dhcp);
		return NULL;
	}

	MASK = FULL_MASK >> subnet_num_of_bits;
	/*ALLOCATE NETWORK*/
	if (SUCCESS != AllocateImp(new_dhcp->root, (ConvertAddress(network_add) & MASK), 
										MAX_BITS - new_dhcp->subnet_num_of_bits))
	{
		DestroySupport(new_dhcp->root);
		free(new_dhcp);
		return NULL;	
	}
	/*ALLOCATE BROADCAST*/
	if (SUCCESS != AllocateImp(new_dhcp->root, (ConvertAddress(broadcast_add) & MASK), 
										MAX_BITS - new_dhcp->subnet_num_of_bits))
	{
		DestroySupport(new_dhcp->root);
		free(new_dhcp);
		return NULL;	
	}
	/*ALLOCATE SERVER*/
	if (SUCCESS != AllocateImp(new_dhcp->root, (ConvertAddress(server_add) & MASK), 
										MAX_BITS - new_dhcp->subnet_num_of_bits))
	{
		DestroySupport(new_dhcp->root);
		free(new_dhcp);
		return NULL;	
	}
	
	return new_dhcp;
}

static size_t ConvertAddress(ip_t address)
{
	size_t output = 0;
	int index = 0;
	for (index = 0; index < CHARIP_SIZE; ++index)
	{
		output <<= BYTE_SHIFT;
		output |= address[index];
	}
	return output;
}

void DHCPDestroy(dhcp_t *dhcp)
{
	ASSERT_NOT_NULL(dhcp);
	if (NULL != dhcp->root)
	{
		DestroySupport(dhcp->root);
	}
	free(dhcp);
}

static void DestroySupport(trie_node_t* node)
{
	if (NULL != node->children[ZERO])
	{
		DestroySupport(node->children[ZERO]);
	}
	if (NULL != node->children[ONE])
	{
		DestroySupport(node->children[ONE]);
	}
	free(node);
	node = NULL;
}

DHCP_status_t DHCPAllocate(dhcp_t *dhcp, ip_t propose_addr, ip_t return_addr)
{
	size_t MASK = FULL_MASK;
	DHCP_status_t status = SYSTEM_FAIL;

	ASSERT_NOT_NULL(dhcp);

	MASK >>= dhcp->subnet_num_of_bits;
	MASK ^= FULL_MASK;	
	if ((ConvertAddress(dhcp->network) & MASK) != 
			(ConvertAddress(propose_addr) & MASK) && 
			0 != ConvertAddress(propose_addr))
	{
		return SYSTEM_FAIL;
	}
	MASK ^= FULL_MASK;
	if (dhcp->root->is_full)
	{
		return SUB_NET_FULL;
	}
	if(0 == ConvertAddress(propose_addr))
	{
		CopyAddress(dhcp->network, return_addr);
		++return_addr[CHARIP_SIZE - 1];
	}
	else
	{
		CopyAddress(propose_addr, return_addr);
	}
	while (SUCCESS != 
		(status = IsFreeAddress(dhcp->root, ConvertAddress(return_addr) & MASK, 
		MAX_BITS - dhcp->subnet_num_of_bits)))
	{/*TODO stop at system failure*/
		if(((ConvertAddress(broadcast_add) & MASK) == (ConvertAddress(return_addr) & MASK)) || 
		((ConvertAddress(server_add) & MASK) == (ConvertAddress(return_addr) & MASK)))
		{
			CopyAddress(dhcp->network, return_addr);
		}

		IncrementReturn(return_addr, CHARIP_SIZE - 1);
	}	
	status = AllocateImp(dhcp->root, ConvertAddress(return_addr) & MASK, 
										MAX_BITS - dhcp->subnet_num_of_bits);
	return status;
}

static void IncrementReturn(ip_t return_addr, int index)
{
	if (0 > index)
	{
		return;
	}
	if (CHAR_MAX == return_addr[index])
	{
		IncrementReturn(return_addr, index - 1);
		return_addr[index] = 0;
	}
	else 
	{
		++return_addr[index];
	}
}

static void CopyAddress(ip_t src, ip_t dest)
{
	size_t index = 0;
	for (index = 0; index < CHARIP_SIZE; ++index)
	{
		dest[index] = src[index];
	}
}

static DHCP_status_t IsFreeAddress(trie_node_t* node, size_t address, size_t shift)
{
	size_t direction = (address >> shift) & BIT_MASK;

	if (node->is_full)
	{
		return SUB_NET_FULL;
	}
	if(NULL == node->children[direction])
	{
		return SUCCESS;
	}
	return IsFreeAddress(node->children[direction], address, shift - 1);
	
}

static DHCP_status_t AllocateImp(trie_node_t* node, size_t address, size_t shift)
{
	size_t direction = (address >> shift) & BIT_MASK;
	DHCP_status_t status = SUCCESS;

	if(NULL == node->children[direction])
	{
		if (0 == shift)
		{
			node->is_full = 1;
			return SUCCESS;
		}
		node->children[direction] = CreateNode();
		if(NULL == node->children[direction])
		{
			return SYSTEM_FAIL;
		}
	}

	status = AllocateImp(node->children[direction], address, shift - 1);

	if ((SUCCESS == status) && (NULL != node->children[direction ^ BIT_MASK]))
	{
		if (node->children[ZERO]->is_full && node->children[ONE]->is_full)
		{
			node->is_full = 1;
		}
	}

	return status;
}

static trie_node_t* CreateNode(void)
{/*TODO*/
	trie_node_t* new_node = malloc(sizeof(struct trie_node));
	if(NULL == new_node)
	{
		return NULL;
	}
	new_node->children[ZERO] = NULL;
	new_node->children[ONE] = NULL;
	new_node->is_full = 0;	
	return new_node;
}

void DHCPFree(dhcp_t *dhcp, ip_t key)
{
	size_t MASK = FULL_MASK;

	ASSERT_NOT_NULL(dhcp);
	MASK >>= dhcp->subnet_num_of_bits;
	MASK ^= FULL_MASK;
	if ((ConvertAddress(dhcp->network) & MASK) != 
											(ConvertAddress(key) & MASK))
	{
		return;
	}
	MASK ^= FULL_MASK;	
	if(((ConvertAddress(network_add) & MASK) == (ConvertAddress(key) & MASK)) || 
	((ConvertAddress(broadcast_add) & MASK) == (ConvertAddress(key) & MASK)) || 
		((ConvertAddress(server_add) & MASK) == (ConvertAddress(key) & MASK)))
	{
		return;
	}


	FreeImp(dhcp->root, (ConvertAddress(key) & MASK), 
										MAX_BITS - dhcp->subnet_num_of_bits);
	
}

static void FreeImp(trie_node_t* node, size_t address, size_t shift)
{
	size_t direction = (address >> shift) & BIT_MASK;	
	node->is_full = 0;
	if(NULL == node->children[direction])
	{
		return;
	}
	FreeImp(node->children[direction], address, shift - 1);
}

size_t CountFree(dhcp_t *dhcp)
{
	size_t max_adds = 0;
	
	ASSERT_NOT_NULL(dhcp);
	
	max_adds = (BIT_MASK << (MAX_BITS - dhcp->subnet_num_of_bits + 1)) - 1;
	return max_adds - CountSupport(dhcp->root, MAX_BITS - dhcp->subnet_num_of_bits);
}

static size_t CountSupport(trie_node_t* node, size_t level)
{
	size_t count = 0;
	if (node->is_full)
	{
		return BIT_MASK << level;
	}
	if (0 == level)
	{
		return 0;
	}
	if(NULL != node->children[ZERO])
	{
		count += CountSupport(node->children[ZERO], level -1);
	}
	if(NULL != node->children[ONE])
	{
		count += CountSupport(node->children[ONE], level -1);
	}

	return count;
}






