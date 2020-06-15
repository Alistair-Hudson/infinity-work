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
    SetPos(Point (xpos, ypos));
    SetColor(Color (color_));
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
    return *this;
}

Square::~Square()
{

}

int Square::GetLength() const
{
    return m_length;
}

void Square::SetLength(int length_)
{
    m_length = length_;
}

void Square::DrawInternal()
{
    Point prel;

    Point p1(GetPos().GetX()+(m_length/2), 
                GetPos().GetY()+(m_length/2));
    prel.SetX(p1.GetX() - GetPos().GetX());
    prel.SetY(p1.GetY() - GetPos().GetY());

    p1.SetX(prel.GetX()*cos(GetAngle())- prel.GetY()*sin(GetAngle()));
    p1.SetY(prel.GetX()*sin(GetAngle())+ prel.GetY()*cos(GetAngle()));

    p1.SetX(p1.GetX()+GetPos().GetX());
    p1.SetY(p1.GetY()+GetPos().GetY());

    Point p2(GetPos().GetX()+(m_length/2), 
                GetPos().GetY()-(m_length/2));
    prel.SetX(p2.GetX() - GetPos().GetX());
    prel.SetY(p2.GetY() - GetPos().GetY());

    p2.SetX(prel.GetX()*cos(GetAngle())- prel.GetY()*sin(GetAngle()));
    p2.SetY(prel.GetX()*sin(GetAngle())+ prel.GetY()*cos(GetAngle()));

    p2.SetX(p2.GetX()+GetPos().GetX());
    p2.SetY(p2.GetY()+GetPos().GetY());

    Point p3(GetPos().GetX()-(m_length/2), 
                GetPos().GetY()-(m_length/2));
    prel.SetX(p3.GetX() - GetPos().GetX());
    prel.SetY(p3.GetY() - GetPos().GetY());

    p3.SetX(prel.GetX()*cos(GetAngle())- prel.GetY()*sin(GetAngle()));
    p3.SetY(prel.GetX()*sin(GetAngle())+ prel.GetY()*cos(GetAngle()));

    p3.SetX(p3.GetX()+GetPos().GetX());
    p3.SetY(p3.GetY()+GetPos().GetY());

    Point p4(GetPos().GetX()-(m_length/2), 
                GetPos().GetY()+(m_length/2));
    prel.SetX(p4.GetX() - GetPos().GetX());
    prel.SetY(p4.GetY() - GetPos().GetY());

    p4.SetX(prel.GetX()*cos(GetAngle())- prel.GetY()*sin(GetAngle()));
    p4.SetY(prel.GetX()*sin(GetAngle())+ prel.GetY()*cos(GetAngle()));

    p4.SetX(p4.GetX()+GetPos().GetX());
    p4.SetY(p4.GetY()+GetPos().GetY());


    DrawPolygon(GetColor().GetColor(), 
            4, 
            p1.GetX(), 
            p1.GetY(), 
            p2.GetX(), 
            p2.GetY(), 
            p3.GetX(), 
            p3.GetY(), 
            p4.GetX(), 
            p4.GetY());
}

/******INTERNAL FUNCTION DECLARATION******/

/*****FUNCTION DEFINITION******/