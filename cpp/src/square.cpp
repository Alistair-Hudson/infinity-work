/******************************************************************************
 *	Title:		Square Class
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	08.06.2020.0
 ******************************************************************************/


#include "square.hpp"

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****STRUCTS*******/

/*****CLASSES******/

/******CLASS FUNCTIONS*******/
Square::Square(int xpos, int ypos, double angle, int length, COLORS color_)
{
    Point m_point(xpos, ypos);
    Color m_color(color_);
    SetAngle(angle);
    m_length = length;
}

Square::Square(const Square& square_)
{
    Point m_point(square_.GetPos());
    Color m_color(square_.GetColor());
    SetAngle(square_.GetAngle());
    m_length = square_.GetLength();
}

Square& Square::operator= (const Square& square_)
{
    Point m_point(square_.GetPos());
    Color m_color(square_.GetColor());
    SetAngle(square_.GetAngle());
    m_length = square_.GetLength();
}

Square::~Square()
{

}

int Square::GetLength() const
{
    return m_length;
}

void Square::DrawInternal()
{
    DrawPolygon(GetColor().GetColor(), 
            4, 
            GetPos().GetX(), 
            GetPos().GetY(), 
            (GetPos().GetX()+m_length*cos(GetAngle())), 
            (GetPos().GetY()+m_length*sin(GetAngle())), 
            (GetPos().GetX()+m_length*cos(GetAngle())+m_length*cos(-GetAngle())), 
            (GetPos().GetY()+m_length*sin(GetAngle())+m_length*sin(-GetAngle())), 
            (GetPos().GetX()+m_length*cos(-GetAngle())), 
            (GetPos().GetY()+m_length*sin(-GetAngle()));
}

/******INTERNAL FUNCTION DECLARATION******/

/*****FUNCTION DEFINITION******/