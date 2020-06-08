/******************************************************************************
 *	Title:		Shapes Test
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	08.06.2020.0
 ******************************************************************************/


#include "line.hpp"
#include "square.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

/******MACROS******/
#define SCREEN_WIDTH    (1000)
#define SCREEN_HEIGHT   (1000)

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****STRUCTS*******/

/*****CLASSES******/

/******CLASS FUNCTIONS*******/

/******INTERNAL FUNCTION DECLARATION******/

static void DrawFunc();

/*****FUNCTION DEFINITION******/

int main(int argc, char** argv)
{
    DrawInit(argc, argv, SCREEN_WIDTH, SCREEN_HEIGHT, DrawFunc);

    
    return 0;
}

static void DrawFunc()
{

}