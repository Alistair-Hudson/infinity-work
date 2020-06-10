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

/*===TARGETING RECTICLE===*/
Line target_vert(SCREEN_WIDTH/2, 
                SCREEN_HEIGHT/2, 
                90, 100, COLOR_RED);
Line target_horiz(SCREEN_WIDTH/2, 
                SCREEN_HEIGHT/2, 
                0, 100, COLOR_RED);

/*===SHAPE TARGETS===*/
Square square(0, 0, 0, 100, COLOR_GREEN);
Circle circle(0, 0, 0, 100, COLOR_YELLOW);

/*****STRUCTS*******/

/*****CLASSES******/

/******CLASS FUNCTIONS*******/

/******INTERNAL FUNCTION DECLARATION******/

static void DrawFunc();
static int KeyCapture(unsigned char key, int x, int y);

/*****FUNCTION DEFINITION******/

int main(int argc, char** argv)
{
    DrawInit(argc, argv, SCREEN_WIDTH, SCREEN_HEIGHT, DrawFunc);
    DrawSetKeyboardFunc(KeyCapture);

    DrawMainLoop();
    
    return 0;
}

static void DrawFunc()
{
    target_horiz.DrawInternal();
    target_vert.DrawInternal();
}

static int KeyCapture(unsigned char key, int x, int y)
{
    Point up_vector(0, 1);
    Point down_vector(0, -1);
    Point left_vector(-1, 0);
    Point right_vector(1, 0);

    switch (key)
    {
    case 27: //ESC key Capture
        return -1;
    
    case 38: //Up arrow key caputre
        target_horiz.Move(up_vector);
        target_vert.Move(up_vector);
        break;
    case 40: //Up arrow key caputre
        target_horiz.Move(up_vector);
        target_vert.Move(up_vector);
        break;
    case 37: //Left arrow key caputre
        target_horiz.Move(left_vector);
        target_vert.Move(left_vector);
        break;
    case 39: //Right arrow key caputre
        target_horiz.Move(right_vector);
        target_vert.Move(right_vector);
        break;
    default:
        break;
    }
    return 0;
}