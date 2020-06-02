/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <stdio.h>

struct X
{

    explicit X(int a_);
    void Foo();
    
private:
    int m_a;
    
};

X::X(int a_): m_a(a_) {}

void X::Foo() 
{
    printf("%d\n", m_a);
}

void Foo(const X &x_)
{
   //printf("%d\n", x_.m_a);
}

int main()
{
    X x1(1);

    x1.Foo();
    //printf("%d\n", x1.m_a);
    Foo(x1);
    
    return 0;
}
