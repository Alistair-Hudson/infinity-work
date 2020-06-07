/******************************************************************************
 *	Title:		Simple String
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	04.06.2020.1
 ******************************************************************************/
#include <iostream> /* std io functions */
#include <string.h> /* strlen, strcmp */

#include "simple_string.hpp"

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****CLASSES******/

/****CLASS FUNCTIONS*****/

String::String(char str[]) //ctor, not explicit in the case that a user wishes to have other data types stored as a string
{
    m_cstr = new char[strlen(str) + 1];
    for (int i = 0; i <= strlen(str); ++i)
    {
        m_cstr[i] = str[i];
    }
    m_cstr[strlen(str) + 1] = '\0';
}

String::String(const String& str)//ctor copy
{
    m_cstr = new char[str.Length() + 1];
    for (int i = 0; i <= str.Length(); ++i)
    {
        m_cstr[i] = str.CStr()[i];
    }
    m_cstr[str.Length() + 1] = '\0';
}

String::~String()//dtor
{
    delete[] m_cstr;
    m_cstr = 0;
}

int String::Length(void) const
{
    return strlen(m_cstr);
}

const char* String::CStr(void) const
{
    return m_cstr;
}

String& String::operator=(const String& other_)
{
    //allocate to temp ptr
    delete[] m_cstr;
    m_cstr = new char[other_.Length() + 1];
    for (int i = 0; i <= other_.Length(); ++i)
    {
        m_cstr[i] = other_.CStr()[i];
    }
    m_cstr[other_.Length() + 1] = '\0';
    return *this; //this is to ensure that a void is not returned
}

/******INTERNAL FUNCTION DECLARATION******/

/*****FUNCTION DEFINITION******/

    bool operator==(const String& s1_, const String& s2_) 
    { 
        return !strcmp(s1_.CStr(), s2_.CStr()); 
    }
    
    bool operator>(const String& s1_, const String& s2_) 
    { 
        return 0 < strcmp(s1_.CStr(), s2_.CStr()); 
    }
    
    bool operator<(const String& s1_, const String& s2_) 
    { 
        return 0 > strcmp(s1_.CStr(), s2_.CStr()); 
    }
    
    bool operator==(const char* o_, const String &str) 
    { 
        return !strcmp(o_, str.CStr()); 
    }
    
    std::ostream& operator<< (std::ostream& os_, const String& x_) 
    {
        return os_ << x_.CStr();
    }