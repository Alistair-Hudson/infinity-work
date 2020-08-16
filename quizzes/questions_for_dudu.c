#include <stdio.h>
#include <string.h>

//"910000000000000000000000000000000000000000000000000000000000000000000"
//find bug on extremely long strings

int SumToTen(const char* str)//added const to prevent the string from being altered
{
    int is_there_LUT[11] = {0};
    
    while ('\0' != *str)
    {
    
        if (is_there_LUT[10 - (*str - '0')])
        {
            return 1;
        }
        is_there_LUT[*str - '0'] = 1; 
        ++str;
    }

    return 0;
}

//Reverse String Recursively
void RecRevImp(char* start, char* end)
{
    if (start >= end)
    {
        return;
    }
    char temp = *start;
    *start = *end;
    *end = temp;
    RecRevImp(++start, --end);
}

char* RecRevStr(char* str)
{
    int l = strlen(str)-1;
    
    RecRevImp(str, str+l);

    return str;



int main ()
{
    char str[] = "910000000000000000000000000000000000000000000000000000000000000000000";
    printf("%s\n", str);
    printf("%s\n", RecRevStr(str));
    return 0;
}