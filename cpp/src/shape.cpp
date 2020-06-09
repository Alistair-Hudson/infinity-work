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
    return *this;
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
Color::Color(COLORS color_)
{
    m_color = color_;
}

Color::Color(const Color& color_)
{
    m_color = color_.m_color;
}

Color& Color::operator= (const Color& color_)
{
    m_color = color_.m_color;
    return *this;
}

Color::~Color()
{

}

COLORS Color::GetColor() const
{
    return m_color;
}

/*===SHAPE CLASS FUNCTIONS===*/
Shape::Shape(int xpos, int ypos, double angle, COLORS color_)
{
    SetPos(Point (xpos, ypos));
    SetColor(Color (color_));
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
    return *this;
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
    m_color = color_.GetColor();
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
    m_angle += delta_angle;
}

void Shape::Revolve(Point c_point, double angle)
{
    Point relative_pos((m_point - c_point));
    double current_angel = atan2(relative_pos.GetX(), relative_pos.GetY());
    current_angel += angle;
    double  hype = hypot(relative_pos.GetX(), relative_pos.GetY());

    relative_pos.SetX(hype*cos(current_angel));
    relative_pos.SetY(hype*sin(current_angel));

    SetPos(relative_pos+c_point);
}

void Shape::Move(Point vector)
{
    m_point = m_point + vector;
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
