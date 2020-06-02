/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

struct X
{
    explicit X();
    
    explicit X(int a_, int b_ = 8);
    ~X();
    X(const X& other_);
    X& operator=(const X& other_);
    
    int m_a;
    const int m_b;
};

X::X(): m_a(3), m_b(4)
{
    //m_a = 3;
    // m_b = 4;
    std::cout << "this:" << this << 
                "X defaault Ctor.m_a:" << m_a <<
                "m_b:" << m_b <<std::endl;
}

X::X(int a_, int b_): m_a(a_), m_b(b_)
{
    std::cout<< "this:" << this <<
                "X int int Ctor.m_a:" << m_a <<
                "m_b:" << m_b << std::endl;
}

X::X(const X& other_): m_a(other_.m_a), m_b(other_.m_b)
{
    std::cout<< "this:" << this <<
                "X copy Ctor.m_a:" << m_a <<
                " m_b:" << m_b << std::endl;
}

X& X::operator=(const X& other_)
{
    m_a= other_.m_a;
    //m_b= other_.m_b;
    std::cout << "this:" << this <<
                "X assignment operator.m_a:" << m_a <<
                "does not change m_b:" << m_b << std::endl;
                
    return *this;
}

X::~X()
{
std::cout << "this:" << this <<
            "X Dtor.m_a:" << m_a <<
            "m_b:" << m_b << std::endl;
}

int main()
{
    X x1;
    X x2(7);
    X *px = new X(x2);
    X x3(9, 10);
    X x4(x1);
    
    x1 = x3;
    
    delete px; px = 0;
    
    return 0;
}
