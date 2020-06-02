/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

template <typename T>
T Max(T t1, T t2)
{
    return (t1 > t2) ? t1: t2;
}

int main()
{
    int arr[12];
    
    std::cout << Max<int>(3,5) << " " << Max<double>(3.7, 12.9) << " ";
    std::cout << Max<int*>(arr, arr+8) << std::endl;
    std::cout << Max('a', 'b') << std::endl;
    return 0;
}
