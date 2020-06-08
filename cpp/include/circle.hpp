#ifndef __OL85_CIRCLE_HPP__
#define __OL85_CIRCLE_HPP__

/*******************************************************************************
                                * OL85 API FOR CIRCLE
                                * version 04.06.2020.0
******************************************************************************/

#include "shape.hpp"

class Circle : public Shape
{
public:
    Circle(int xpos = 0, int ypos = 0, double angle = 0, int radius = 0);
    Circle(const Circle& Circle_);
    Circle& operator= (const Circle& Circle_);
    ~Circle();

    int GetRadius() const;
    void DrawInternal();
    
private:
    int m_radius;

};

#endif /* __OL85_CIRCLE_HPP__ */