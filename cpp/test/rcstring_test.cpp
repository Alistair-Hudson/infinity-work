/******************************************************************************
 *	Title:		RCString Main
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	27.05.2020.0
 ******************************************************************************/
#include <iostream> /* std io functions */
#include <string.h> /* strlen, strcmp, strdup */

#include "rcstring.hpp"

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****CLASSES******/

/******INTERNAL FUNCTION DECLARATION******/

/*****FUNCTION DEFINITION******/

int main()
{
   RCString str1 = "Hello ";
   RCString str2(str1);
   RCString str3(str1);
   
   str2 = "world!";
   
   std::cout << "str1 = " << str1.ToCStr() << std::endl;
   std::cout << "str2 = " << str2.ToCStr() << std::endl;
   std::cout << "length of str1 = " << str1.Length() << std::endl;
   std::cout << "character at positon 1 = " << str1[1] << std::endl;
   std::cout << "str1 == str2: " << (str1==str2) << std::endl;
   std::cout << "str1 != str2: " << (str1!=str2) << std::endl;
   std::cout << "str1 < str2: " << (str1<str2) << std::endl;
   std::cout << "str1 > str2: " << (str1>str2) << std::endl;
   
   str1.Concat(str2);
   std::cout << "Concat str1 = " << str1.ToCStr() << std::endl;
   std::cout << "str3 = " << str3 << std::endl;
    return 0;
}
