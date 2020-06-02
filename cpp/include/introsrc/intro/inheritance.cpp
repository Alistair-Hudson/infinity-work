/******************************************************************************
 *	Title:		Simple String
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	27.05.2020.0
 ******************************************************************************/
#include <iostream> /* std io functions */
#include <string.h> /* strlen, strcpy, strdup */

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****CLASSES******/
class B
{
public:
    B(int a_ = 8):m_a(a_)
    {
        std::cout << "B::Ctor" << std::endl;
    }
    virtual ~B()
    {
        std::cout << "B::Dtor" << std::endl;
    }
    
    virtual void Print1() const;
    virtual void Print2() const;
    virtual void Print3() const;
    
private:
    
    int m_a;
};

class X: public B
{
public:
    X():m_b(0)
    {
        std::cout << "X::Ctor" << std::endl;
    }
    ~X()
    {
        std::cout << "X::Dtor" << std::endl;
    }
    
    virtual void Print1() const
    {
        std::cout << "X::Print1 X::m_b - " << m_b << std::endl;
        B::Print1();
        std::cout << "X::Print1 end" << std::endl;
    }
    
    void Print2() const
    {
        std::cout << "X::Print2" << std::endl;
    }
    
private:
    int m_b;
};

/******CLASS FUNCTIONS*******/
void B::Print1() const
{
    std::cout << "B::Print1 B::m_a - " << m_a << std::endl;
}

void B::Print2() const
{
    std::cout << "B::Print2" << std::endl;
}

void B::Print3() const
{
    std::cout << "B::Print3" << std::endl;
}

/******INTERNAL FUNCTION DECLARATION******/

/*****FUNCTION DEFINITION******/

int main()
{
    B *b1 = new B;
    B *b2 = new X;
    
    std::cout << std::endl << "main b1:" << std::endl;
    b1->Print1();
    b1->Print2();
    b1->Print3();
    
    X *xx = static_cast<X*>(b2);
    std::cout << std::endl << "main xx:" << std::endl;
    xx->Print2();
    b2->Print2();
    b2->Print3();
    
    delete b1;
    delete b2;
    
    return 0;
}