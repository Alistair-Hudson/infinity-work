/******************************************************************************
 *	Title:		Complex Numbers
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	16.06.2020.1
 ******************************************************************************/
#include <iostream>     /* std io functions */
#include <string>       /* strlen, strcpy, strdup */
#include <exception>
#include <cstdlib>

#include "complex_numbers.hpp"

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****STRUCTS*******/

/*****CLASSES******/

/******CLASS FUNCTIONS*******/
Complex::Complex(int real = 0, int imag = 0) : m_real(real), m_imag(imag) 
{

}

Complex::Complex(const Complex& complex)
{
    m_real = complex.m_real;
    m_imag = complex.m_imag;
}

Complex::~Complex() 
{

}

void Complex::SetReal(int real)
{
    m_real = real;
}

void Complex::SetImag(int imag)
{
    m_imag = imag;
}

int Complex::GetReal()const
{
    return m_real;
}

int Complex::GetImag() const
{
    return m_imag;
}

/******INTERNAL FUNCTION DECLARATION******/

/*****FUNCTION DEFINITION******/
Complex operator+(const Complex& comp1, const Complex& comp2)
{
    Complex output(0, 0);
    output.SetReal(comp1.GetReal()+comp2.GetReal());
    output.SetImag(comp1.GetImag()+comp2.GetImag());
    return output;
}

Complex operator-(const Complex& comp1, const Complex& comp2)
{
    Complex output(0, 0);
    output.SetReal(comp1.GetReal()-comp2.GetReal());
    output.SetImag(comp1.GetImag()-comp2.GetImag());
    return output;
}

Complex operator*(const Complex& comp1, const Complex& comp2)
{   
    Complex output(0,0);
    output.SetReal(comp1.GetReal()*comp2.GetReal() - comp1.GetImag()*comp2.GetImag());
    output.SetImag(comp1.GetReal()*comp2.GetImag() + comp1.GetImag()*comp2.GetReal());
    return output;
}

Complex operator/(const Complex& comp1, const Complex& comp2)
{
    Complex output(0,0);
    int denominator = comp2.GetReal()*comp2.GetReal() + comp2.GetImag()*comp2.GetImag();
    output.SetReal((comp1.GetReal()*comp2.GetReal() + comp1.GetImag()*comp2.GetImag())/denominator);
    output.SetImag((comp1.GetImag()*comp2.GetReal() - comp1.GetReal()*comp2.GetImag())/denominator);
    return output;
}

bool operator==(const Complex& comp1, const Complex& comp2)
{
    return (comp1.GetReal() == comp2.GetReal() ? comp1.GetImag() == comp2.GetImag() ? 1 : 0 : 0);
}

bool operator!=(const Complex& comp1, const Complex& comp2)
{
    return !(comp1 == comp2);
}

std::ostream& operator<< (std::ostream& os_, const Complex& complex)
{
    return os_ << complex.GetReal() << "+" << complex.GetImag() << "i";
}

std::istream& operator>> (std::istream& is_, Complex& complex)
{
    int real;
    int imag;
    is_ >> real >> imag;
    complex.SetReal(real);
    complex.SetImag(imag);
}