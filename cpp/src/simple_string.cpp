/******************************************************************************
 *	Title:		Simple String
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	27.05.2020.0
 ******************************************************************************/
#include <iostream> /* std io functions */
#include <string.h> /* strlen, strcpy, strdup */

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****CLASSES******/
class String
{
public:
    String(char str[]) //ctor
    {
        m_cstr = strdup(str);
    }
    String(const String& str)//ctor copy
    {
        m_cstr = strdup(str.m_cstr);
    }
    ~String()//dtor
    {
        m_cstr = 0;
    }
    int Length(void)
    {
        return strlen(m_cstr);
    }
    char* CStr(void)
    {
        return m_cstr;
    }
    String& operator=(const String& other_)
    {
        m_cstr = other_.m_cstr;
        return *this;
    }
    bool operator==(const String& o_) const 
    { 
        return m_cstr == o_.m_cstr; 
    }
    bool operator>(const String& o_) const 
    { 
        return m_cstr > o_.m_cstr; 
    }
    bool operator<(const String& o_) const 
    { 
        return m_cstr < o_.m_cstr; 
    }
    friend bool operator==(const char* o_, const String &str) 
    { 
        return !strcmp(o_, str.m_cstr); 
    }
    friend std::ostream& operator<< (std::ostream& os_, const String& x_) 
    {
        return os_ << x_.m_cstr;
    }
    
private:
    
    char* m_cstr;
};

/******INTERNAL FUNCTION DECLARATION******/

/*****FUNCTION DEFINITION******/

int main()
{
    String s1("hello");
    String s2(s1);

    s1 = s2;
    
    std::cout << s1.CStr() << std::endl;
    std::cout << s1.Length() << std::endl;
    std::cout << s1 << std::endl;
    return 0;
}
