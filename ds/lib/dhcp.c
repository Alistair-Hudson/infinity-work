/******************************************************************************
 *	Title:		DHCP
 *	Authour:	Alistair Hudson
 *	Reviewer:	Shmuel
 *	Version:	30.03.2020.0
 ******************************************************************************/
#include <stdlib.h>
#include <assert.h>		/* assert */

#include "dhcp.h"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))
#define MAX_BITS				(32)
#define FULL_MASK				(~0x0)
#define BIT_MASK				(1)
#define BYTE_SHIFT				(8)

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

static trie_node_t* CreateNode(void);

static void FreeImp(trie_node_t* node, size_t address, size_t shift);

static size_t SizeSupport(trie_node_t* node);

static void DestroySupport(trie_node_t* node);

static size_t ConvertAddress(ip_t address);

/******FUNCTIONS******/
dhcp_t *DHCPCreate(ip_t network, size_t subnet_num_of_bits)
{
	size_t MASK = 0;

	dhcp_t* new_dhcp = malloc(sizeof(struct dhcp));
	if(NULL == new_dhcp)
	{
		return NULL;
	}

	new_dhcp->network[0] = network[0];
	new_dhcp->network[1] = network[1];
	new_dhcp->network[2] = network[2];
	new_dhcp->network[3] = network[3];
	new_dhcp->subnet_num_of_bits = subnet_num_of_bits;

	new_dhcp->root = CreateNode();
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
		output |= address[index];
		output <<= BYTE_SHIFT;
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
	size_t MASK = 0;

	ASSERT_NOT_NULL(dhcp);
	
	if (dhcp->network != 0/*start of propose_addr*/)
	{
		return SYSTEM_FAIL;
	}
	MASK = FULL_MASK >> dhcp->subnet_num_of_bits;

	return AllocateImp(dhcp->root, ConvertAddress(propose_addr) & MASK, 
										MAX_BITS - dhcp->subnet_num_of_bits);

}

static DHCP_status_t AllocateImp(trie_node_t* node, size_t address, size_t shift)
{
	size_t direction = (address >> shift) & BIT_MASK;
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
		return AllocateImp(node->children[direction], address, shift - 1);
	}
	if (node->is_full)
	{
		return SUB_NET_FULL;
	}	
	if(SUB_NET_FULL == AllocateImp(node->children[direction], address, shift - 1))
	{
		return AllocateImp(node->children[direction ^ BIT_MASK], address, shift - 1);
	}

	return AllocateImp(node->children[direction], address, shift - 1);
}

static trie_node_t* CreateNode(void)
{
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
	size_t MASK = 0;

	ASSERT_NOT_NULL(dhcp);
	if (dhcp->network != 0/*start of propose_addr*/)
	{
		return;
	}
	
	if(/*network address*/0 == key || 0/*broadcast address*/ == key || 
													0/*server address*/ == key)
	{
		return;
	}
	MASK = FULL_MASK >> dhcp->subnet_num_of_bits;

	FreeImp(dhcp->root, (ConvertAddress(network_add) % MASK), 
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
	return 0;
}

static size_t CountSupport(trie_node_t* node)
{
/*	if (NULL != node->children[ZERO])
	{
		count += CountSupport(node->children[ZERO]);
	}
	if (NULL != node->children[ONE])
	{
		count += node->children[ONE];
	}
*/	return 0;
}






