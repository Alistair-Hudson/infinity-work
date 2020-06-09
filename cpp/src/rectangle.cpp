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
    SetPos(Point (xpos, ypos));
    SetColor(Color (color_));
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
    return *this;
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
                (int)(GetPos().GetX()+m_length*(int)cos(GetAngle())), 
                (int)(GetPos().GetY()+m_length*(int)sin(GetAngle())), 
                (int)(GetPos().GetX()+m_length*(int)cos(GetAngle())+m_width*(int)sin(GetAngle())), 
                (int)(GetPos().GetY()+m_length*(int)sin(GetAngle())+m_width*(int)cos(GetAngle())), 
                (int)(GetPos().GetX()+m_width*(int)sin(GetAngle())), 
                (int)(GetPos().GetY()+m_width*(int)cos(GetAngle())));
}

/******INTERNAL FUNCTION DECLARATION******/

/*****FUNCTION DEFINITION******/