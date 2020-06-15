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

/*****STRUCTS ENUMKS AND UNIONS*******/
enum DIRECTION
{
    LEFT = -1,
    RIGHT = 1
};

/*****CLASSES******/
class Barrel : public Circle
{
public:
    Barrel( int xpos = 0, 
            int ypos = 0, 
            double angle = 0, 
            int radius = 0,
            COLORS color_ = COLOR_WHITE);
    Barrel(const Barrel& barrel_);
    Barrel& operator= (const Barrel& Circle_);
    ~Barrel();

    enum DIRECTION GetDir() const;
    void SetDir(const DIRECTION dir);
    
private:
    enum DIRECTION m_dir;

};

class Ladder : public Rectangle
{
public:
    Ladder( int xpos = 0, 
            int ypos = 0, 
            double angle = 0, 
            int length = 0,
            int width = 0,
            COLORS color_ = COLOR_WHITE);
    Ladder(const Ladder& ladder_);
    Ladder& operator= (const Ladder& ladder_);
    ~Ladder();

};

/******CLASS FUNCTIONS*******/
/*===BARREL METHODS===*/
Barrel::Barrel(int xpos, int ypos, double angle, int radius, COLORS color_)
{
    SetPos(Point (xpos, ypos));
    SetColor(Color (color_));
    SetAngle(angle);
    SetRadius(radius);
    m_dir = LEFT;
}

Barrel::Barrel(const Barrel& Circle_)
{
    SetPos(Circle_.GetPos());
    SetColor(Circle_.GetColor());
    SetAngle(Circle_.GetAngle());
    SetRadius(Circle_.GetRadius());
    m_dir = Circle_.GetDir();
}

Barrel& Barrel::operator= (const Barrel& circle_)
{
    SetPos(circle_.GetPos());
    SetColor(circle_.GetColor());
    SetAngle(circle_.GetAngle());
    SetRadius(circle_.GetRadius());
    m_dir = circle_.GetDir();
    return *this;
}

Barrel::~Barrel()
{

}
enum DIRECTION Barrel::GetDir() const
{
    return m_dir;
}

void Barrel::SetDir(enum DIRECTION dir_)
{
    m_dir = dir_;
}

/*===LADDER METHODS===*/
Ladder::Ladder(int xpos, int ypos, double angle, int length, int width, COLORS color_)
{
    SetPos(Point (xpos, ypos));
    SetColor(Color (color_));
    SetAngle(angle);
    SetLength(length);
    SetWidth(width);
}

Ladder::Ladder(const Ladder& Circle_)
{
    SetPos(Circle_.GetPos());
    SetColor(Circle_.GetColor());
    SetAngle(Circle_.GetAngle());
    SetLength(Circle_.GetLength());
    SetWidth(Circle_.GetWidth());
}

Ladder& Ladder::operator= (const Ladder& circle_)
{
    SetPos(circle_.GetPos());
    SetColor(circle_.GetColor());
    SetAngle(circle_.GetAngle());
    SetLength(circle_.GetLength());
    SetWidth(circle_.GetWidth());
    return *this;
}

Ladder::~Ladder()
{
}

/****** GLOBAL VARIABLES*****/

/*===PLAYER===*/
Circle player(5, 
                SCREEN_HEIGHT-30, 
                0, 25, COLOR_GREEN);

/*===BARRELS===*/
Barrel barrel(SCREEN_WIDTH+25, 170, 0, 25, COLOR_YELLOW);

std::list<Barrel> barrel_list;

/*===LEVELS===*/
Line ground(SCREEN_WIDTH/2, 
            SCREEN_HEIGHT-5, 
            0, SCREEN_WIDTH, COLOR_BLUE);

Line level1(SCREEN_WIDTH/2, 
            SCREEN_HEIGHT-205, 
            0, SCREEN_WIDTH, COLOR_BLUE);
Line level2(SCREEN_WIDTH/2, 
            SCREEN_HEIGHT-405, 
            0, SCREEN_WIDTH, COLOR_BLUE);
Line level3(SCREEN_WIDTH/2, 
            SCREEN_HEIGHT-605, 
            0, SCREEN_WIDTH, COLOR_BLUE);
Line level4(SCREEN_WIDTH/2, 
            SCREEN_HEIGHT-805, 
            0, SCREEN_WIDTH, COLOR_BLUE);

/*===LADDERS===*/
Ladder ladder1(SCREEN_WIDTH-100,
                SCREEN_HEIGHT-105,
                0, 2, 200, COLOR_RED);
Ladder ladder2(100,
                SCREEN_HEIGHT-305,
                0, 2, 200, COLOR_RED);
Ladder ladder3(SCREEN_WIDTH-100,
                SCREEN_HEIGHT-505,
                0, 2, 200, COLOR_RED);
Ladder ladder4(100,
                SCREEN_HEIGHT-705,
                0, 2, 200, COLOR_RED);

std::list<Ladder> ladder_list;

static int jump_count = 0;
static int barrel_delay = 0;
Rectangle finish_line(SCREEN_WIDTH-50, 0, 0, 2, 400, COLOR_WHITE);

/******INTERNAL FUNCTION DECLARATION******/

static void DrawFunc();
static int KeyCapture(unsigned char key, int x, int y);
static int TimedEvents();
static void DrawBarrels();
static void DrawLadders();
static void MoveAll();
static int CheckAll();
static void LevelCheck(const Line& level);
static void AddTarget();

/*****FUNCTION DEFINITION******/

int main(int argc, char** argv)
{
    barrel_list.push_back(barrel);
    ladder_list.push_back(ladder1);
    ladder_list.push_back(ladder2);
    ladder_list.push_back(ladder3);
    ladder_list.push_back(ladder4);
    

    DrawInit(argc, argv, SCREEN_WIDTH, SCREEN_HEIGHT, DrawFunc);
    DrawSetKeyboardFunc(KeyCapture);
    DrawSetTimerFunc(TimedEvents, 100);

    DrawMainLoop();
    
    return 0;
}

static void DrawFunc()
{
    player.DrawInternal();
    ground.DrawInternal();
    level1.DrawInternal();
    level2.DrawInternal();
    level3.DrawInternal();
    level4.DrawInternal();
    finish_line.DrawInternal();
    DrawLadders();
    DrawBarrels();
    //DrawLadders();
}

static int KeyCapture(unsigned char key, int x, int y)
{
    Point up_vector(0, -5);
    Point down_vector(0, 5);
    Point left_vector(-5, 0);
    Point right_vector(5, 0);
    Point jump(0, -50);
    Point reset(rand()%SCREEN_WIDTH, rand()%SCREEN_HEIGHT);

    std::list<Ladder>::iterator iter = ladder_list.begin();

    switch (key)
    {
    case 27: //ESC key Capture
        return -1;
    
    case 'w': //W key caputre
        while(iter != ladder_list.end())
        {
            if (iter->GetPos().GetX() == player.GetPos().GetX() &&
                player.GetPos().GetY()+player.GetRadius() <= iter->GetPos().GetY() + iter->GetWidth()/2 && 
                player.GetPos().GetY()+player.GetRadius() >= iter->GetPos().GetY() - iter->GetWidth()/2)
            {
                player.Move(up_vector);
        
            }
            iter = next(iter, 1);    
        }
        break;
    case 's': //S key caputre
        while(iter != ladder_list.end())
        {
            if (iter->GetPos().GetX() == player.GetPos().GetX() &&
                (player.GetPos().GetY()+player.GetRadius() <= iter->GetPos().GetY() + iter->GetWidth()/2 && 
                player.GetPos().GetY()+player.GetRadius() >= iter->GetPos().GetY() - iter->GetWidth()/2))
            {
                player.Move(down_vector);
        
            }
            iter = next(iter, 1);    
        }
        break;
    case 'a': //A key caputre
        player.Move(left_vector);
        break;
    case 'd': //D key caputre
        player.Move(right_vector);
        break;
    case ' ': // Space key cpature
        if (0 == jump_count)
        {
            player.Move(jump);
            jump_count = 15;
        }
        break;
    default:
        break;
    }
    return 0;
}

static int TimedEvents()
{
    MoveAll();
    
    
    --barrel_delay;
    if (0 == rand()%15 && 0 >= barrel_delay)
    {
        Barrel new_barrel(barrel);
        barrel_list.push_back(barrel);
        barrel_delay = 30;
    }
    //AddTarget();
    return CheckAll();
}

static void DrawBarrels()
{
    std::list<Barrel>::iterator iter = barrel_list.begin();

    while(iter != barrel_list.end())
    {
       iter->DrawInternal();
       iter = next(iter, 1);
    }
}

static void DrawLadders()
{
    std::list<Ladder>::iterator iter = ladder_list.begin();

    while(iter != ladder_list.end())
    {
       iter->DrawInternal();
       iter = next(iter, 1);
    }
}

void MoveAll()
{
    std::list<Barrel>::iterator iter = barrel_list.begin();
    Point vector(5, 0);

    while(iter != barrel_list.end())
    {
        vector.SetX(vector.GetX()*iter->GetDir());
        vector.SetY(0);
        iter->Move(vector);
        if(-iter->GetRadius() >= SCREEN_WIDTH -iter->GetPos().GetX())
        {
            vector.SetY(100);
            iter->SetDir(LEFT);
            iter->Move(vector);
        }
        if(-iter->GetRadius() >= iter->GetPos().GetX())
        {
            vector.SetY(100);
            iter->SetDir(RIGHT);
            iter->Move(vector);
        }
        vector.SetY(0);
        vector.SetX(5);
        iter = next(iter, 1);
    } 
}

static int CheckAll()
{
    if (SCREEN_HEIGHT < barrel_list.begin()->GetPos().GetY())
    {
        barrel_list.pop_front();
    }

    std::list<Barrel>::iterator iter = barrel_list.begin();
    Point reset(5, 
                SCREEN_HEIGHT-30);
    
    if (0 < jump_count)
    {
        --jump_count;
    }
    if (1 == jump_count)
    {
        LevelCheck(ground);
    }

    while (iter != barrel_list.end())
    {
        if (player.GetPos().GetY()-iter->GetPos().GetY() < iter->GetRadius() &&
            player.GetPos().GetY()-iter->GetPos().GetY() > -iter->GetRadius()&&
            player.GetPos().GetX()-iter->GetPos().GetX() < iter->GetRadius() && 
            player.GetPos().GetX()-iter->GetPos().GetX() > -iter->GetRadius())
        {
            player.SetPos(reset);
        }
        iter = next(iter, 1);
    }

    if (player.GetPos().GetX() > finish_line.GetPos().GetX())
    {
        std::cout << "Congrats You Win!!!!!" << std::endl;
        return -1;

    }
    return 1;
}

static void LevelCheck(const Line& level)
{
    Point invert_jump(0, 50);
    if (player.GetPos().GetY() < (level.GetPos().GetY()-player.GetRadius()))
    {
        player.Move(invert_jump);
    }
}

static void AddTarget()
{
    Point start_pos(0, 0);
    switch(rand()%50)
    {
        case (5):
            start_pos.SetX(rand()%SCREEN_WIDTH);
            break;
        default:
            break;
    }
}