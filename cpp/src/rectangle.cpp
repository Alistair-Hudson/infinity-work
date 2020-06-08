/******************************************************************************
 *	Title:		Rectangle Class
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	08.06.2020.0
 ******************************************************************************/


#include "rectangle.hpp"

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****STRUCTS*******/

/*****CLASSES******/

/******CLASS FUNCTIONS*******/
Rectangle::Rectangle(   int xpos, 
                        int ypos, 
                        double angle, 
                        int length, 
                        int width, 
                        COLORS color_)
{
    Point m_point(xpos, ypos);
    Color m_color(color_);
    SetAngle(angle);
    m_length = length;
}

Rectangle::Rectangle(const Rectangle& rectangle_)
{
    Point m_point(rectangle_.GetPos());
    Color m_color(rectangle_.GetColor());
    SetAngle(rectangle_.GetAngle());
    m_length = rectangle_.GetLength();
    m_width = rectangle_.GetWidth();
}

Rectangle& Rectangle::operator= (const Rectangle& rectangle_)
{
    Point m_point(rectangle_.GetPos());
    Color m_color(rectangle_.GetColor());
    SetAngle(rectangle_.GetAngle());
    m_length = rectangle_.GetLength();
    m_width = rectangle_.GetWidth();
}

Rectangle::~Rectangle()
{

}

int Rectangle::GetLength() const
{
    return m_length;
}

int Rectangle::GetWidth() const
{
    return m_width;
}

void Rectangle::DrawInternal()
{
    DrawPolygon(GetColor().GetColor(), 
                4, 
                GetPos().GetX(), 
                GetPos().GetY(), 
                (GetPos().GetX()+m_length*cos(GetAngle())), 
                (GetPos().GetY()+m_length*sin(GetAngle())), 
                (GetPos().GetX()+m_length*cos(GetAngle())+m_width*cos(-GetAngle())), 
                (GetPos().GetY()+m_length*sin(GetAngle())+m_width*sin(-GetAngle())), 
                (GetPos().GetX()+m_width*cos(-GetAngle())), 
                (GetPos().GetY()+m_width*sin(-GetAngle()));
}

/******INTERNAL FUNCTION DECLARATION******/

/*****FUNCTION DEFINITION******/