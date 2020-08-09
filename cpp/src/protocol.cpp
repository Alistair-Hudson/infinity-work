/******************************************************************************
 *	Title:		Protocol
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	05.08.2020.0
 ******************************************************************************/

#include <iostream>

#include "protocol.hpp"

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****STRUCTS*******/

/*****CLASSES******/

/*****FUNCTORS*****/

/******INTERNAL FUNCTION DECLARATION******/

/******CLASS METHODS*******/

/*****FUNCTION DEFINITION******/

int main()
{
    ilrd::Request req = {0, 0, 0, 0};

    std::cout << "re size = " << req.RequestSize() << std::endl;

    return 0;
}