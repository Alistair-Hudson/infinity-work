/******************************************************************************
 *	Title:		Shapes Test
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	08.06.2020.0
 ******************************************************************************/

#include <iostream>

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
static int TimedEvents();

/*****FUNCTION DEFINITION******/

int main(int argc, char** argv)
{
    DrawInit(argc, argv, SCREEN_WIDTH, SCREEN_HEIGHT, DrawFunc);
    DrawSetKeyboardFunc(KeyCapture);
    DrawSetTimerFunc(TimedEvents, 100);

    DrawMainLoop();
    
    return 0;
}

static void DrawFunc()
{
    target_horiz.DrawInternal();
    target_vert.DrawInternal();
    square.DrawInternal();
}

static int KeyCapture(unsigned char key, int x, int y)
{
    Point up_vector(0, -5);
    Point down_vector(0, 5);
    Point left_vector(-5, 0);
    Point right_vector(5, 0);
    Point reset(rand()%SCREEN_WIDTH, rand()%SCREEN_HEIGHT);

    switch (key)
    {
    case 27: //ESC key Capture
        return -1;
    
    case 'w': //W key caputre
        target_horiz.Move(up_vector);
        target_vert.Move(up_vector);
        break;
    case 's': //S key caputre
        target_horiz.Move(down_vector);
        target_vert.Move(down_vector);
        break;
    case 'a': //A key caputre
        target_horiz.Move(left_vector);
        target_vert.Move(left_vector);
        break;
    case 'd': //D key caputre
        target_horiz.Move(right_vector);
        target_vert.Move(right_vector);
        break;
    case ' ': // Space key cpature
        if (target_horiz.GetPos().GetX()-square.GetPos().GetX() < square.GetLength()/2 && 
            target_horiz.GetPos().GetX()-square.GetPos().GetX() > -square.GetLength()/2 && 
            target_horiz.GetPos().GetY()-square.GetPos().GetY() < square.GetLength()/2 && 
            target_horiz.GetPos().GetY()-square.GetPos().GetY() > -square.GetLength()/2)
        {
            square.SetPos(reset);
        }
        break;
    default:
        break;
    }
    return 0;
}

static int TimedEvents()
{
    int vert_dir = (rand()%2 == 0) ? 1 : -1;
    int horiz_dir = (rand()%2 == 0) ? 1 : -1;

    Point vector(1, 1);//(horiz_dir*(rand()%5), vert_dir*(rand()%5));
    Point reset(rand()%SCREEN_WIDTH, rand()%SCREEN_HEIGHT);

    square.Move(vector);
    if (square.GetPos().GetX() > SCREEN_WIDTH ||
        square.GetPos().GetX() < 0 ||
        square.GetPos().GetY() > SCREEN_HEIGHT ||
        square.GetPos().GetY() > 0)
    {
        square.SetPos(reset);
    }

    return 1;
}