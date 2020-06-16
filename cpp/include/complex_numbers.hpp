#ifndef __OL85_COMPLEX_HPP__
#define __OL85_COMPLEX_HPP__

/*******************************************************************************
                                * OL85 API FOR COMPLEX
                                * version 16.06.2020.0
******************************************************************************/
#include <iostream>

class Complex
{
public:
    Complex(int real = 0, int imag = 0);
    Complex(const Complex& complex);
    ~Complex();
    
    void SetReal(int real);
    void SetImag(int imag);
    int GetReal() const;
    int GetImag() const;
    
private:
    int m_real;
    int m_imag;
};

Complex operator+(const Complex& comp1, const Complex& comp2);
Complex operator-(const Complex& comp1, const Complex& comp2);
Complex operator*(const Complex& comp1, const Complex& comp2);
Complex operator/(const Complex& comp1, const Complex& comp2);

bool operator==(const Complex& comp1, const Complex& comp2);
bool operator!=(const Complex& comp1, const Complex& comp2);

std::ostream& operator<< (std::ostream& os_, const Complex& complex);
std::istream& operator>> (std::istream& is_, Complex& complex);

#endif /* __OL85_COMPLEX_HPP__ */