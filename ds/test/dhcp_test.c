#include <stdio.h>
#include <stdlib.h>

#include "dhcp.h"

#define ALL_PASS (3)

int AddressIsEqual(ip_t add1, ip_t add2)
{
	size_t index = 0;
	for(index = 0; index < CHARIP_SIZE; ++index)
	{
		if (add1[index] != add2[index])
		{
			return 0;
		}
	}
	return 1;
}

int Stage1Test()
{
	dhcp_t *dhcp = NULL;
	ip_t network = {192, 168, 1, 0};
	size_t subnet_bits = 24;

	printf("\n\nStage 1 test\n");

	dhcp = DHCPCreate(network, subnet_bits);
	if (NULL == dhcp)
	{
		printf("Create faile\n");
		return 0;
	}

	if (253 != CountFree(dhcp))
	{
		printf("Count Free failed\n");
		printf("%d\n",CountFree(dhcp));
	}
		

	DHCPDestroy(dhcp);
	
	printf("passed\n");
	return 1;
}

int AllocateTest()
{
	dhcp_t *dhcp = NULL;
	ip_t network = {192, 168,1, 0};
	ip_t not_in_network = {193, 165, 1, 5};
	ip_t auto_add = {0, 0, 0, 0};
	ip_t added_add = {192, 168, 1, 68};
	ip_t broadcast_add = {192, 168, 1, 255};
	ip_t return_addr = {0, 0, 0, 0};
	size_t subnet_bits = 24;


	printf("\n\nAllocate test\n");
	dhcp = DHCPCreate(network, subnet_bits);

	if (SYSTEM_FAIL != DHCPAllocate(dhcp, not_in_network, return_addr))
	{
		printf("Allocate to wrong network failed\n");
		DHCPDestroy(dhcp);
		return 0;
	}
	
	if (SUCCESS != DHCPAllocate(dhcp, added_add, return_addr))
	{
		printf("Allocate w/out success failed\n");
		DHCPDestroy(dhcp);
		return 0;
	}
	if (!AddressIsEqual(added_add, return_addr))
	{
		printf("Allocate failed\n");
		DHCPDestroy(dhcp);
		return 0;
	}

	if (SUCCESS != DHCPAllocate(dhcp, broadcast_add, return_addr))
	{
		printf("Allocate Broadcast address w/out success failed\n");
		DHCPDestroy(dhcp);
		return 0;
	}
	printf("%d, %d, %d, %d\n", return_addr[0], return_addr[1], return_addr[2], return_addr[3]);
	if (AddressIsEqual(broadcast_add, return_addr))
	{
		printf("Allocate broadcast address failed\n");
		DHCPDestroy(dhcp);
		return 0;
	}

	if (SUCCESS != DHCPAllocate(dhcp, added_add, return_addr))
	{
		printf("Allocate taken address w/out success failed\n");
		DHCPDestroy(dhcp);
		return 0;
	}
	added_add[3] += 2;
	if (!AddressIsEqual(added_add, return_addr))
	{
		printf("Allocate taken address failed\n");
		DHCPDestroy(dhcp);
		return 0;
	}

	if (SUCCESS != DHCPAllocate(dhcp, auto_add, return_addr))
	{
		printf("Allocate auto address w/out success failed\n");
		DHCPDestroy(dhcp);
		return 0;
	}
	DHCPAllocate(dhcp, auto_add, return_addr);
	auto_add[0] = network[0];
	auto_add[1] = network[1];
	auto_add[2] = network[2];
	auto_add[3] = network[3];
	auto_add[3] += 6;
	if (!AddressIsEqual(auto_add, return_addr))
	{
		printf("Allocate auto address failed\n");
		printf("%d, %d, %d, %d\n", return_addr[0], return_addr[1], return_addr[2], return_addr[3]);
		DHCPDestroy(dhcp);
		return 0;
	}

	DHCPDestroy(dhcp);

	printf("passed\n");
	return 1;
}

int FreeTest()
{
	dhcp_t *dhcp = NULL;
	ip_t network = {192, 168, 0, 0};
	ip_t broadcast = {192, 168,  255, 255};
	ip_t server = {192, 168, 255, 254};
	ip_t not_in_network = {193, 165, 1, 5};
	ip_t return_addr = {0, 0, 0, 0};
	ip_t auto_add = {0, 0, 0, 0};
	size_t subnet_bits = 16;
	size_t num_free = 0;

	printf("\n\nFree test\n");
	dhcp = DHCPCreate(network, subnet_bits);
	num_free = CountFree(dhcp);
	
	DHCPFree(dhcp, not_in_network);
	if (num_free != CountFree(dhcp))
	{
		printf("Free from wrong network failed\n");
		DHCPDestroy(dhcp);
		return 0;
	}
	DHCPFree(dhcp, network);
	if (num_free != CountFree(dhcp))
	{
		printf("Attempt to Free network failed\n");
		DHCPDestroy(dhcp);
		return 0;
	}
	DHCPFree(dhcp, broadcast);
	if (num_free != CountFree(dhcp))
	{
		printf("Attempt to Free broadcast failed\n");
		DHCPDestroy(dhcp);
		return 0;
	}
	DHCPFree(dhcp, server);
	if (num_free != CountFree(dhcp))
	{
		printf("Atempt to Free server failed\n");
		DHCPDestroy(dhcp);
		return 0;
	}
	DHCPAllocate(dhcp, auto_add, return_addr);
	DHCPAllocate(dhcp, auto_add, return_addr);
	DHCPFree(dhcp, return_addr);
	if ((num_free - 1) != CountFree(dhcp))
	{
		printf("Atempt to Free failed\n");
		DHCPDestroy(dhcp);
		return 0;
	}

	DHCPDestroy(dhcp);

	printf("passed\n");
	return 1;
}

int main()
{
	
	size_t pass = 0;

	pass += Stage1Test();
	pass += AllocateTest();
	pass += FreeTest();
		
	if (ALL_PASS == pass)
	{
		printf("\n\n\nALL PASSED\n\n\n");
	}
	return 0;
}

