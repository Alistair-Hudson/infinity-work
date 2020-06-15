#ifndef __OL85_SQUARE_HPP__
#define __OL85_SQUARE_HPP__

/*******************************************************************************
                                * OL85 API FOR SQUARE
                                * version 08.06.2020.0
******************************************************************************/

#include "shape.hpp"

class Square : public Shape
{
public:
    Square( int xpos = 0, 
            int ypos = 0, 
            double angle = 0, 
            int length = 0, 
            COLORS color_ = COLOR_WHITE);
    Square(const Square& Square_);
    Square& operator= (const Square& Square_);
    ~Square();

    int GetLength() const;
    void SetLength(int length_);
    void DrawInternal();
    
private:
    int m_length;

};

#endif /* __OL85_SQUARE_HPP__ */