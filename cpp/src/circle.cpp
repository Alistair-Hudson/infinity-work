/******************************************************************************
 *	Title:		Circle Class
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	08.06.2020.0
 ******************************************************************************/


#include "circle.hpp"


/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****STRUCTS*******/

/*****CLASSES******/

/******CLASS FUNCTIONS*******/
Circle::Circle(int xpos, int ypos, double angle, int radius, COLORS color_)
{
    Point m_point(xpos, ypos);
    Color m_color(color_);
    SetAngle(angle);
    m_radius = radius;
}

Circle::Circle(const Circle& Circle_)
{
    Point m_point(Circle_.GetPos());
    Color m_color(Circle_.GetColor());
    SetAngle(Circle_.GetAngle());
    m_radius = Circle_.GetRadius();
}

Circle& Circle::operator= (const Circle& circle_)
{
    Point m_point(circle_.GetPos());
    Color m_color(circle_.GetColor());
    SetAngle(circle_.GetAngle());
    m_radius = circle_.GetRadius();
}

Circle::~Circle()
{

}

int Circle::GetRadius() const
{
    return m_radius;
}

void Circle::DrawInternal()
{
    DrawCircle( GetColor().GetColor(), 
                GetPos().GetX(), 
                GetPos().GetY(), 
                GetRadius());
}

/******INTERNAL FUNCTION DECLARATION******/

/*****FUNCTION DEFINITION******/