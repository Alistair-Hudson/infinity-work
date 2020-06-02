/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

struct X
{
    explicit X(int);
    ~X();
    void Foo();
    void Bar() const;
    
    int m_a;
    int* m_p;
    
};

X::X(int a_): m_a(a_), m_p(new int(a_)) {}

X::~X() {delete m_p; m_p=0;}

void X::Foo() {++m_a; --(*m_p);}

void X::Bar() const
{
    std::cout << m_a << std::endl;
    std::cout << *m_p << std::endl;
    std::cout << m_p << std::endl;
    m_a = 0;
    m_p = 0;
    *m_p = 0;
    Foo();
}

void Fifi(const X& x_)
{
    x_.Foo();
    x_.Bar();
}

int main()
{
    X x1(1);

    x1.Foo();
    Fifi(x1);
    
    return 0;
}
