#ifndef __OL85_LINE_HPP__
#define __OL85_LINE_HPP__

/*******************************************************************************
                                * OL85 API FOR LINE
                                * version 04.06.2020.0
******************************************************************************/

#include "shape.hpp"

class Line : public Shape
{
public:
    Line(int xpos = 0, int ypos = 0, double angle = 0, int length = 0);
    Line(const Line& line_);
    Line& operator= (const Line& line_);
    ~Line();

    int GetLength() const;
    void DrawInternal();

private:
    int m_length;

};


#endif /* __OL85_LINE_HPP__ */