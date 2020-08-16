#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Question 1
int FlipDigitsInNum(int x)
{
    int is_neg = 1;
    if (0 > x)
    {
        is_neg = -1;
    }
    int ret = 0;
    while (x)
    {
        ret *= 10;
        ret += x%10;
        x /= 10;
    }

    return ret*is_neg;
}

//Question 4
char ByteMirror(char byte)
{
    byte = ((byte & 0xf0) >> 4)|((byte & 0x0f) << 4);
    byte = ((byte & 0xcc) >> 2)|((byte & 0x33) << 2);
    byte = ((byte & 0xaa) >> 1)|((byte & 0x55) << 1);
    
    return byte;
}

//Question 5
int FlipBit(int val, unsigned int n)
{
    return val ^ (1 << n);
}

//Question 6
size_t BitCount(char byte)
{
    size_t count = 0;
    while (byte)
    {
        byte &= byte-1;
        ++count;
    }

    return count;
}

//Question 8
char RotateLeft(char byte, unsigned int nbits)
{
    nbits = nbits % 8;
    return (byte << nbits) | (byte >> (8 - nbits));
}

//Question 10
void Swap(int* p1, int* p2)
{
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

//Question 11
size_t Strlen(const char* str)
{
    size_t count  = 0;
    while (*str)
    {
        ++count;
        ++str;
    }
    return count;
}

char* Strcpy(char* dest, const char* src)
{
    char* start = dest;
    while (*src)
    {
        *dest = *src;
        ++dest;
        ++src;
    }
    *dest = 0;
    return start;
}

char* Strncpy(char*dest, const char* src, int n)
{
    char* start = dest;
    while (*src && n > 0)
    {
        *dest = *src;
        ++src;
        ++dest;
        --n;
    }

    while (n > 0)
    {
        *dest = 0;
        ++dest;
    }

    return start;
}

char* Strcat(char* dest, const char* src)
{
    char* start = dest;
    dest += strlen(dest);
    while (*src)
    {
        *dest = *src;
    }
    *dest = 0;
    return start;
}

//Question 12
unsigned long GetNFibonacciElement(unsigned int n)
{
    if (2 == n || 1 == n)
    {
        return 1;
    }

    return GetNFibonacciElement(n-2) + GetNFibonacciElement(n-1);
}

//question 13
char* IntToString(int x, char* str)
{
    sprintf(str, "%d", x);
    return str;
}

//Question 14
size_t MultiplyBy8(size_t x)
{
    return x << 3;
}

//Question 15
void Swap1(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void Swap2(int* x, int* y)
{
    *x += *y;
    *y = *x -*y;
    *x -= *y;
}

void Swap3(int* x, int* y)
{
    *x ^= *y;
    *y ^= *x;
    *x ^= *y;
}