#include <stdlib.h>
#include <stdio.h>

int DoesSumExist(int* array, size_t array_size, int sum)
{
    int* left = array;
    int* right = array + array_size -1;

    while (left < right)
    {
        if (sum == (*left + *right))
        {
            return 1;
        }
        
        if (*left == *right)
        {
            return 0;
        }

        if (sum > (*left + *right))
        {
            ++left;
        }
        else
        {
            --right;
        }
    }
    return 0;
}

int main()
{
    int arr1[] = {2,5,7,8,11,15};
    int arr2[] = {2,5,5,15};

    printf("Does array {2,5,7,8,11,15} have a sum of 16: %d\n", DoesSumExist(arr1, sizeof(arr1)/sizeof(int), 16));
    printf("Does array {2,5,7,8,11,15} have a sum of 3: %d\n", DoesSumExist(arr1, sizeof(arr1)/sizeof(int), 3));
    printf("Does array {2,5,5,15} have a sum of 16: %d\n", DoesSumExist(arr2, sizeof(arr2)/sizeof(int), 16));
    printf("Does array {2,5,5,15} have a sum of 10: %d\n", DoesSumExist(arr2, sizeof(arr2)/sizeof(int), 10));

    return 0;
}