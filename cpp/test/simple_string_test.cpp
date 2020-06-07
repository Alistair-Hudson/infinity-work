/******************************************************************************
 *	Title:		Simple String Main
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	27.05.2020.0
 ******************************************************************************/
#include <iostream> /* std io functions */
#include <string.h> /* strlen, strcmp, strdup */

#include "simple_string.hpp"

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****CLASSES******/

/******INTERNAL FUNCTION DECLARATION******/

/*****FUNCTION DEFINITION******/

int main()
{
    String s1("hello");
    String s2(s1);

    s1 = s2;
    
    std::cout << s1.CStr() << std::endl;
    std::cout << s1.Length() << std::endl;
    std::cout << s1 << std::endl;
    return 0;
}
