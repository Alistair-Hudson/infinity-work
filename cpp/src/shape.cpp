/******************************************************************************
 *	Title:		Shape Class
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	08.06.2020.0
 ******************************************************************************/


#include "shape.hpp"

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****STRUCTS*******/

/*****CLASSES******/

/******CLASS FUNCTIONS*******/
/*===POINT CLASS FUNCTIONS===*/
Point::Point(int x_, int y_)
{
    m_x = x_;
    m_y = y_;
}

Point::Point(const Point& point_)
{
    m_x = point_.GetX();
    m_y = point_.GetY();
}

Point& Point::operator= (const Point& point_)
{
    m_x = point_.GetX();
    m_y = point_.GetY();
}

Point::~Point()
{

}

int Point::GetX() const
{
    return m_x;
}

int Point::GetY() const
{
    return m_y;
}

void Point::SetX(int x_)
{
    m_x = x_;
}

void Point::SetY(int y_)
{
    m_y = y_;
}

/*===COLOR CLASS FUNCTIONS===*/
Color::Color()
{

}

Color::Color(const Color& color_)
{

}

Color& Color::operator= (const Color& color_)
{

}

Color::~Color()
{

}

/*===SHAPE CLASS FUNCTIONS===*/
Shape::Shape(int xpos, int ypos, double angle)
{
    Point m_point(xpos, ypos);
    m_angle = angle;
}

Shape::Shape(const Shape& shape_)
{
    Point m_point(shape_.GetPos());
    Color m_color(shape_.GetColor());
    m_angle = shape_.GetAngle();
}

Shape& Shape::operator= (const Shape& shape_)
{
    Point m_point(shape_.GetPos());
    Color m_color(shape_.GetColor());
    m_angle = shape_.GetAngle();
}

Shape::~Shape()
{

}

Point Shape::GetPos() const
{
    return m_point;
}

Color Shape::GetColor() const
{
    return m_color;
}
double Shape::GetAngle() const
{
    return m_angle;
}

void Shape::SetPos(Point point_)
{
    m_point.SetX(point_.GetX());
    m_point.SetY(point_.GetY());
}

void Shape::SetColor(Color color_)
{

}

void Shape::SetAngle(double angle_)
{
    m_angle = angle_;
}

void Shape::Draw()
{

}

void Shape::DrawInternal()
{

}

void Shape::Rotate(double delta_angle)
{

}

void Shape::Revolve(Point c_point, double angle)
{

}

void Shape::Move(Point vector)
{

}


/******INTERNAL FUNCTION DECLARATION******/

/*****FUNCTION DEFINITION******/

Point& operator+ (const Point& p1, const Point& p2)
{
    Point output((p1.GetX()+p2.GetX()), (p1.GetY()+p2.GetY()));
    return output;
}

Point& operator- (const Point& p1, const Point& p2)
{
    Point output((p1.GetX()-p2.GetX()), (p1.GetY()-p2.GetY()));
    return output;
}

bool operator== (const Point& p1, const Point& p2)
{
    return (p1.GetX()==p2.GetX() ? (p1.GetY()==p2.GetY() ? 1 : 0) : 0);
}
