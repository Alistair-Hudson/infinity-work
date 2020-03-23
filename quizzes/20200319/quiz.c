#include <stdio.h>
#include <stdlib.h>

typedef struct node node_t;

struct node
{
	int data;
	node_t* next;
};

node_t* FindImp(node_t* node1, node_t* node2, size_t n)
{

	if (NULL == node2->next)
	{
		return node1;
	}
	if (0 == n)
	{
		return FindImp(node1->next, node2->next, 0);
	}
	return FindImp(node1, node2->next, --n);

}

node_t* FindNFromEnd(node_t* node, size_t n)
{
	return FindImp(node, node->next, n);
}

int main()
{
	node_t node5 = {5, NULL};
	node_t node4 = {4, &node5};
	node_t node3 = {3, &node4};
	node_t node2 = {2, &node3};
	node_t node1 = {1, &node2};

	node_t* nodeptr = FindNFromEnd(&node1, 2);

	printf("node %d\n", nodeptr->data);
	return 0;
}
