
#include <stdlib.h>
#include <stdio.h>

struct Node;

struct Node
{
    int value;
    struct Node* next;
};

struct Node* Pivot(struct Node* head, int x)
{
    struct Node* less = (struct Node*)malloc(sizeof(struct Node));
    struct Node* greater = (struct Node*)malloc(sizeof(struct Node));
    struct Node* equal = (struct Node*)malloc(sizeof(struct Node));

    struct Node* s_less = less;
    struct Node* s_great = greater;
    struct Node* s_equal = equal;


    while (head)
    {
        if(x > head->value)
        {
            less->next = head;
            less = less->next;
        }
        else if (x < head->value)
        {
            greater->next = head;
            greater = greater->next;
        }
        else
        {
            equal->next = head;
            equal = equal->next;
        }
        head = head->next;
    }
    greater->next = NULL;
    equal->next = s_great->next;
    less->next = s_equal->next;
    head =  s_less->next;

    free(s_less);
    free(s_great);
    free(s_equal);

    return head;
}

int main()
{
    struct Node node1 = {5, NULL};
    struct Node node2 = {1, &node1};
    struct Node node3 = {7, &node2};
    struct Node node4 = {4, &node3};
    struct Node node5 = {2, &node4};

    struct Node* ret = Pivot(&node5, 3);

    while (ret)
    {
        printf("%d\n", ret->value);
        ret = ret->next;
    }

    return 0;
}