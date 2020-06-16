/******************************************************************************
 *	Title:		Complex Numbers Testfile
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	16.06.2020.1
 ******************************************************************************/
#include <iostream>     /* std io functions */
#include <string>       /* strlen, strcpy, strdup */
#include <exception>
#include <cstdlib>

#include "complex_numbers.hpp"

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****STRUCTS*******/

/*****CLASSES******/

/******CLASS FUNCTIONS*******/

/******INTERNAL FUNCTION DECLARATION******/

/*****FUNCTION DEFINITION******/
int main()
{
    Complex complex1(2,3);
    Complex complex2(complex1);
    int test = 0;
    int test2 = 0;
    
    std::cin >> complex1;
    std::cout << complex1 << std::endl; 
    return 0;
}