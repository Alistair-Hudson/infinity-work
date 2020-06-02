/******************************************************************************
 *	Title:		Complex Numbers
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	01.06.2020.0
 ******************************************************************************/
#include <iostream>     /* std io functions */
#include <string>       /* strlen, strcpy, strdup */
#include <exception>
#include <cstdlib>

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****STRUCTS*******/

/*****CLASSES******/
class Complex
{
public:
    Complex(int real = 0, int imag = 0) : m_real(real), m_imag(imag) {}
    Complex(const Complex& complex)
    {
        m_real = complex.m_real;
        m_imag = complex.m_imag;
    }
    ~Complex() {}
    
    void operator+(const Complex& complex)
    {
        m_real += complex.m_real;
        m_imag += complex.m_imag;
    }
    void operator-(const Complex& complex)
    {
        m_real -= complex.m_real;
        m_imag -= complex.m_imag;
    }
    void operator*(const Complex& complex)
    {
        m_real = m_real*complex.m_real - m_imag*complex.m_imag;
        m_imag = m_real*complex.m_imag - m_imag*complex.m_real;
    }
    void operator/(const Complex& complex)
    {
        int denominator = complex.m_real*complex.m_real + complex.m_imag*complex.m_imag;
        m_real = (m_real*complex.m_real + m_imag*complex.m_imag)/denominator;
        m_imag = (m_imag*complex.m_real - m_real*complex.m_imag)/denominator;
    }
    
    bool operator==(const Complex& complex)
    {
        return m_real == complex.m_real ? m_imag == complex.m_imag ? 1 : 0 : 0;
    }
    bool operator!=(const Complex& complex)
    {
        return m_real != complex.m_real ? 1 : m_imag != complex.m_imag ? 1 : 0;
    }
    
    void SetReal(int real)
    {
        m_real = real;
    }
    void SetImag(int imag)
    {
        m_imag = imag;
    }
    int GetReal()
    {
        return m_real;
    }
    int GetImag()
    {
        return m_imag;
    }
    
    friend std::ostream& operator<< (std::ostream& os_, const Complex& complex)
    {
       return os_ << complex.m_real << "+" << complex.m_imag << "i";
    }
    friend std::istream& operator>> (std::istream& is_, Complex& complex)
    {
        is_ >> complex.m_real >> complex.m_imag;
    }
    
private:
    int m_real;
    int m_imag;
};

/******CLASS FUNCTIONS*******/

/******INTERNAL FUNCTION DECLARATION******/

/*****FUNCTION DEFINITION******/

int main()
{
    Complex complex1(2,3);
    Complex complex2(complex1);
    int test = 0;
    int test2 = 0;
    
    std::cin >> complex1;
    std::cout << complex1 << std::endl; 
    return 0;
}