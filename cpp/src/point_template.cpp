/******************************************************************************
 *	Title:		Point Template Class
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	14.06.2020.0
 ******************************************************************************/

#include <iostream>

/******MACROS******/

/******TYPEDEFS*****/

/*****STRUCTS*******/

/*****CLASSES******/
template <typename T>
class Point
{
public:
    Point(T x_, T y_);
    
    inline void SetX(T x_);
    inline void SetY(T y_);
    inline T GetX() const;
    inline T GetY() const;
    
    Point& operator+=(const Point& p2);
    Point& operator-=(const Point& p2);

private:
    T m_x;
    T m_y;
};

/******CLASS FUNCTIONS*******/
template <typename T>
Point<T>::Point(T x_, T y_):m_x(x_), m_y(y_)
{
    
}

template <typename T>
void Point<T>::SetX(T x_)
{
    m_x = x_;
}

template <typename T>
void Point<T>::SetY(T y_)
{
    m_y = y_;
}

template <typename T>
T Point<T>::GetX() const
{
    return m_x;
}

template <typename T>
T Point<T>::GetY() const
{
    return m_y;
}

template <typename T>
Point<T>& Point<T>::operator+=(const Point<T>& p2)
{
    m_x += p2.GetX();
    m_y += p2.GetY();
    return *this;
}

template <typename T>
Point<T>& Point<T>::operator-=(const Point<T>& p2)
{
    m_x -= p2.GetX();
    m_y -= p2.GetY();
    return *this;
}

template <typename T>
Point<T> operator+(const Point<T>& p1, const Point<T>& p2)
{
    Point<T> output(p1.GetX()+p2.GetX(), p1.GetY()+p2.GetY());
    return output;
}

template <typename T>
Point<T> operator-(const Point<T>& p1, const Point<T>& p2)
{
    Point<T> output(p1.GetX()-p2.GetX(), p1.GetY()-p2.GetY());
    return output;
}

/****** GLOBAL VARIABLES*****/

/******INTERNAL FUNCTION DECLARATION******/

/*****FUNCTION DEFINITION******/
int main()
{
    Point<int> i1(1,1);
    Point<int> i2(i1);
    
    i1+=i2;
    
    std::cout << i1.GetX() << "," << i1.GetY() << std::endl;
    Point<int> i3 = i2 + i1;
    std::cout << i3.GetX() << "," << i3.GetY() << std::endl;
    
    return 0;
}