#ifndef __OL85_SIMPLE_STRING_HPP__
#define __OL85_SIMPLE_STRING_HPP__

/*******************************************************************************
                                * OL85 API FOR SIMPLE STRING
                                * version 04.06.2020.0
******************************************************************************/
#include <iostream>

class String
{
public:
    String(char str[]); //ctor
    String(const String& str);//ctor copy
    ~String();//dtor
    int Length(void) const;
    const char* CStr(void) const;
    String& operator=(const String& other_);
    
private:
    
    char* m_cstr;
};

bool operator==(const String& s1_, const String& s2_);

bool operator>(const String& s1_, const String& s2_);

bool operator<(const String& s1_, const String& s2_);

bool operator==(const char* o_, const String &str);

std::ostream& operator<< (std::ostream& os_, const String& x_);

#endif /* __OL85_SIMPLE_STRING_HPP__ */
