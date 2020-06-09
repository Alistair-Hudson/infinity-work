#include <stdio.h>
#include <mcheck.h>

#include "glut_utils.h"
#include "rectangle.hpp"
#include "circle.hpp"
#include "line.hpp"
#include "square.hpp"


int drawCircle = 1;
int xCircle = 250;
int yCircle = 100;
double rCircle = 100;

Circle circle(xCircle, yCircle, 0, rCircle, COLOR_GREEN);
Square rect(500, 500, 0, 100, COLOR_RED);

static void DrawFunction();
static int KeyboardFunction(unsigned char key, int x, int y);
static int MouseFunction(int button, int state, int x, int y);
static int MotionFunction(int x, int y);
static int TimerFunction();


int main(int argc, char** argv)
{
    /*--------------------------- mtrace(); */

    DrawInit(argc, argv, 1000, 1000, DrawFunction);

    /* advanced: extra functionality */
    DrawSetKeyboardFunc(KeyboardFunction);
    DrawSetMouseFunc(MouseFunction);
    DrawSetMotionFunc(MotionFunction);
    DrawSetTimerFunc(TimerFunction, 100);

    DrawMainLoop();

    printf("exit\n");

    return 0;
}


static void DrawFunction()
{
    /* printf("Drawing\n"); */

    /* draw rectangle */     

    rect.DrawInternal();

    if (drawCircle)
        
        circle.DrawInternal();
        
}


static int KeyboardFunction(unsigned char key, int x, int y)
{
    printf("Keyboard: %02x,%d,%d\n", key, x, y);

    if (key == 0x1b /* ESC */)
        return -1;

    return 0;
}


static int MouseFunction(int button, int state, int x, int y)
{
    /* printf("Mouse: %d,%d,%d,%d\n", button, state, x, y); */

    if (state == 1 && button == MOUSE_WHEEL_UP)
    {
        rCircle *= 1.1;
        return 1;
    }
    if (state == 1 && button == MOUSE_WHEEL_DOWN)
    {
        rCircle *= 0.9;
        return 1;
    }

    if (button == MOUSE_LEFT)
    {
        drawCircle = state;
        return 1;
    }

    return 0;
}


static int MotionFunction(int x, int y)
{
    printf("Mouse: %d,%d\n", x, y);

    return 0;
}


static int TimerFunction()
{
    circle.Revolve((500, 500), 1);
    rect.Rotate(1);

    return 1;  /* draw */
}
