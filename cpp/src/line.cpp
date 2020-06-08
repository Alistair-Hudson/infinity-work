/******************************************************************************
 *	Title:		Line Class
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	08.06.2020.0
 ******************************************************************************/


#include "line.hpp"

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****STRUCTS*******/

/*****CLASSES******/

/******CLASS FUNCTIONS*******/
Line::Line(int xpos, int ypos, double angle, int length, COLORS color_)
{
    Point m_point(xpos, ypos);
    Color m_color(color_);
    SetAngle(angle);
    m_length = length;
}

Line::Line(const Line& line_)
{
    Point m_point(line_.GetPos());
    Color m_color(line_.GetColor());
    SetAngle(line_.GetAngle());
    m_length = line_.GetLength();
}

Line& Line::operator= (const Line& line_)
{
    Point m_point(line_.GetPos());
    Color m_color(line_.GetColor());
    SetAngle(line_.GetAngle());
    m_length = line_.GetLength();
}

Line::~Line()
{

}

int Line::GetLength() const
{
    return m_length;
}

void Line::DrawInternal()
{
    
    DrawPolygon(GetColor().GetColor(), 
                2, 
                GetPos().GetX(), 
                GetPos().GetY(), 
                (GetPos().GetX()+m_length*cos(GetAngle())), 
                (GetPos().GetY()+m_length*sin(GetAngle()));
}

/******INTERNAL FUNCTION DECLARATION******/

/*****FUNCTION DEFINITION******/