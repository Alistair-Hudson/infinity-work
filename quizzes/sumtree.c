#include <stdlib.h>
#include <stdio.h>


struct Node;

struct Node
{
    int val;
    struct Node* left;
    struct Node* right;
};

int SumTree(struct Node* node)
{
    if (NULL == node->left)
    {
        return node->val;
    }

    return SumTree(node->left) + SumTree(node->right);
}

int main()
{
    struct Node leaf1 = {1, NULL, NULL};
    struct Node leaf2 = {1, NULL, NULL};
    struct Node leaf3 = {1, NULL, NULL};
    struct Node leaf4 = {1, NULL, NULL};

    struct Node sub1 = {0, &leaf1, &leaf2};
    struct Node sub2 = {0, &leaf3, &leaf4};

    struct Node root = {0, &sub1, &sub2};

    printf("%d", SumTree(&root));

    return 0;
    
}