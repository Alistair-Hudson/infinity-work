#ifndef __OL85_SHAPE_HPP__
#define __OL85_SHAPE_HPP__

/*******************************************************************************
                                * OL85 API FOR SHAPE
                                * version 08.06.2020.0
******************************************************************************/

#include <cmath>

#include "glut_utils.h"

class Point
{
public:
    Point(int x_ = 0, int y_ = 0);
    Point(const Point& point_);
    Point& operator= (const Point& point_);
    ~Point();

    int GetX() const;
    int GetY() const;
    
    void SetX(int x_);
    void SetY(int y_);

private:
    int m_x;
    int m_y;
};

class Color
{
public:
    Color(COLORS color_ = COLOR_WHITE);
    Color(const Color& color_);
    Color& operator= (const Color& color_);
    ~Color();

    COLORS GetColor() const;

private:
    COLORS m_color;
};

class Shape
{
public:
    Shape(int xpos = 0, int ypos = 0, double angle = 0, COLORS color_ = COLOR_WHITE);
    Shape(const Shape& shape_);
    Shape& operator= (const Shape& shape_);
    ~Shape();

    Point GetPos() const;
    Color GetColor() const;
    double GetAngle() const;

    void SetPos(Point point_);
    void SetColor(Color color_);
    void SetAngle(double angle_);

    void Draw();

    virtual void DrawInternal();
    virtual void Rotate(double delta_angle);
    virtual void Revolve(Point c_point, double angle);
    virtual void Move(Point vector);

private:
    Point m_point;
    Color m_color;
    double m_angle;
};

Point& operator+ (const Point& p1, const Point& p2);
Point& operator- (const Point& p1, const Point& p2);
bool operator== (const Point& p1, const Point& p2);


#endif /* __OL85_SHAPE_HPP__ */