/******************************************************************************
 *	Title:		Shapes Test
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	08.06.2020.0
 ******************************************************************************/

#include <iostream>
#include <list>
#include <iterator>

#include "line.hpp"
#include "square.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

/******MACROS******/
#define SCREEN_WIDTH    (1000)
#define SCREEN_HEIGHT   (1000)

/******TYPEDEFS*****/

/*****STRUCTS*******/

/*****CLASSES******/

/******CLASS FUNCTIONS*******/

/****** GLOBAL VARIABLES*****/

/*===TARGETING RECTICLE===*/
Line target_vert(SCREEN_WIDTH/2, 
                SCREEN_HEIGHT/2, 
                90, 100, COLOR_RED);
Line target_horiz(SCREEN_WIDTH/2, 
                SCREEN_HEIGHT/2, 
                0, 100, COLOR_RED);

/*===SHAPE TARGETS===*/
Square square(0, 0, 0, 100, COLOR_YELLOW);
Circle circle(0, 0, 0, 100, COLOR_YELLOW);
Square square2(0, 0, 0, 100, COLOR_GREEN);
std::list<Square> target_list;

/******INTERNAL FUNCTION DECLARATION******/

static void DrawFunc();
static int KeyCapture(unsigned char key, int x, int y);
static int TimedEvents();
static void DrawAll();
static void MoveAll();
static void CheckAll();
static void AddTarget();

/*****FUNCTION DEFINITION******/

int main(int argc, char** argv)
{
    target_list.push_back(square);
    target_list.push_back(square);
    target_list.push_back(square);
    target_list.push_back(square2);


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
    DrawAll();
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
        CheckAll();
        break;
    default:
        break;
    }
    return 0;
}

static int TimedEvents()
{
    MoveAll();
    AddTarget();
    return 1;
}

static void DrawAll()
{
    std::list<Square>::iterator iter = target_list.begin();

    while(iter != target_list.end())
    {
       iter->DrawInternal();
       iter = next(iter, 1);
    }
}

void MoveAll()
{
    std::list<Square>::iterator iter = target_list.begin();
    Point vector(0, 0);

    while(iter != target_list.end())
    {
        vector.SetX(5-(rand()%10));
        vector.SetY(rand()%5);
        iter->Move(vector);
        iter = next(iter, 1);
    } 
}

static void CheckAll()
{
    std::list<Square>::iterator iter = target_list.begin();
    Point reset(0, 0);

    while (iter != target_list.end())
    {
        if (target_horiz.GetPos().GetX()-iter->GetPos().GetX() < iter->GetLength()/2 && 
            target_horiz.GetPos().GetX()-iter->GetPos().GetX() > -iter->GetLength()/2 && 
            target_horiz.GetPos().GetY()-iter->GetPos().GetY() < iter->GetLength()/2 && 
            target_horiz.GetPos().GetY()-iter->GetPos().GetY() > -iter->GetLength()/2)
        {
            reset.SetX(rand()%SCREEN_WIDTH);
            iter->SetPos(reset);
        }
        iter = next(iter, 1);
    }
}

static void AddTarget()
{
    Point start_pos(0, 0);
    switch(rand()%50)
    {
        case (5):
            start_pos.SetX(rand()%SCREEN_WIDTH);
            target_list.push_back(square);
            target_list.end()->SetPos(start_pos);
            break;
        default:
            break;
    }
}