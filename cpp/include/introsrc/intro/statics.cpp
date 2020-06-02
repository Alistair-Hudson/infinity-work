/******************************************************************************
 *	Title:		Sratic EX28
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
    explicit X() : m_id(++s_cntr) {}
    int GetId() {std::cout << m_id << std::endl; return m_id;}
private:
    int m_id;
    static int s_cntr;
};

/******CLASS FUNCTIONS*****/
int X::s_cntr = 0;

/******INTERNAL FUNCTION DECLARATION******/

/*****FUNCTION DEFINITION******/

int main()
{
    X x1;
    X x2;
    
    x1.GetId();
    x2.GetId();
    
    return 0;
}

