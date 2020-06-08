#ifndef __OL85_RECTANGLE_HPP__
#define __OL85_RECTANGLE_HPP__

/*******************************************************************************
                                * OL85 API FOR RECTANGLE
                                * version 08.06.2020.0
******************************************************************************/

#include "shape.hpp"

class Rectangle : public Shape
{
public:
    Rectangle(  int xpos = 0, 
                int ypos = 0, 
                double angle = 0, 
                int length = 0,
                int width = 0, 
                COLORS color_ = COLOR_WHITE);
    Rectangle(const Rectangle& Rectangle_);
    Rectangle& operator= (const Rectangle& Rectangle_);
    ~Rectangle();

    int GetLength() const;
    int GetWidth() const;
    void DrawInternal();
    
private:
    int m_length;
    int m_width;

};

#endif /* __OL85_RECTANGLE_HPP__ */