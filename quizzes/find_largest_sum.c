
#include <stdlib.h>

struct Node
{
    int value;
    struct Node* left;
    struct Node* right;
    struct Node* parent1;
    struct Node* parent2;
};

int LargestSumNiave(struct Node* root)
{
    int return_value = root->value;

    if (NULL == root->left)
    {
        return return_value;
    }

    if (root->left->value >= root->right->value)
    {
        return  return_value + LargestSumNiave(root->left);
    }

    return return_value + LargestSumNiave(root->right);

}

int LargestSumBetter(struct Node* root)
{
    int left_sum = 0;
    int right_sum = 0;

    if (NULL == root->left)
    {
        return root->value;
    }

    if ((left_sum = root->value+LargestSumBetter(root->left)) >= 
        (right_sum = root->value+LargestSumBetter(root->right)))
    {
        return left_sum;
    }
    return right_sum;
}
