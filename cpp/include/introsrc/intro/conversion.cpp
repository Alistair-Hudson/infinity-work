/******************************************************************************
 *	Title:		Intro EX27
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	28.05.2020.0
 ******************************************************************************/
#include <iostream> /* std io functions */
#include <string.h> /* strlen, strcpy, strdup */

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****CLASSES******/
class X
{
public:
    explicit X();
    X(int a_);
    X(int a_, int b_);
    
    operator int() const;
    void Print() const;
    
private:
    
    int m_a;
};

/******CLASS FUNCTIONS*****/
X::X() : m_a(0) {}

X::X(int a_) : m_a(a_) {}

X::X(int a_, int b_) : m_a(a_ + b_) {}

X::operator int()const
{
    return m_a;
}

void X::Print() const
{
    std::cout << "X::Print() " << m_a << std::endl;
}

void Fifi(X x_)
{
    std::cout << "Fifi() " << x_ << std::endl;
}

/******INTERNAL FUNCTION DECLARATION******/

/*****FUNCTION DEFINITION******/

int main()
{
    X x1(7);
    
    Fifi(x1); //(1)
    Fifi(X(8)); //(2)
    Fifi(9); //(3)
    Fifi(X(3, 2)); //(4)
    
    return x1 *3; //(5)
}

