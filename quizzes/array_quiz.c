// A = {1, 2, 3, 4} then B = {24, 12, 8, 6}

#include <stdio.h>
#include <stdlib.h>

void ArrayMaker( int*a, int* b, size_t size)
{
    int prod = 1;

    for (int i = 0; i < size; ++i)
    {
        prod *= a[i];
    }

    for (int i = 0; i < size; ++i)
    { 
        b[i] = prod / a[i];
    }
}


int main()
{
    int a[5] = {1,2,3,4,5};
    int b[5] = {0};

    ArrayMaker(a, b, 5);
    
    printf("a b\n");
    for (int i = 0; i < 5; ++i)
    {
        printf ("%d %d\n", a[i], b[i]);
    }
    return 0;
}