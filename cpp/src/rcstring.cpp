/******************************************************************************
 *	Title:		RC String
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	04.06.2020.1
 ******************************************************************************/
#include <iostream>     /* std io functions */
#include <string.h>       /* strlen, strcmp */
#include <exception>
#include <cstdlib>

#include "rcstring.hpp"

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****STRUCTS*******/

/*****CLASSES******/


/******CLASS FUNCTIONS*******/
RCString::RCString(const char* str_): strhld(new string_holder)
{
    strhld->str = const_cast<char*>(str_);
    strhld->instances = 1;
}

RCString::RCString(const RCString& o_): strhld(o_.strhld)
{
    ++strhld->instances;
}

RCString::~RCString()
{
    --strhld->instances;
    if (0==strhld->instances)
    {
        delete strhld;
    }
}

RCString& RCString::operator=(const RCString& o_)
{
    if (this == &o_ || strhld == o_.strhld)
    {
        return *this;
    }
    --strhld->instances;
    if (0 == strhld->instances)
    {
        delete strhld;
    }
    strhld = o_.strhld;
    ++strhld->instances;
    return *this;
}

const char* RCString::ToCStr() const
{
    return strhld->str;
}

size_t RCString::Length() const
{
    return strlen(strhld->str);
}

char RCString::operator[](size_t idx_) const
{
    if (Length() < idx_)
    {
        return '\0';
    }
    return strhld->str[idx_];
}

char& RCString::operator[](size_t idx_)
{
    /*if(Length() < idx_)
    {
        return '\0';
    }
    */int length = Length();
    
    char* strbuffer = new char[length];
    strcpy(strbuffer, ToCStr());
    
    --strhld->instances;
    if(0 == strhld->instances)
    {
        delete strhld;
    }
    
    strhld = new (string_holder);
    strhld->str = strbuffer;
    ++strhld->instances;
    
    return strhld->str[idx_];
}

RCString& RCString::Concat(const RCString& o_)
{
    int length1 = Length();
    int length2 = o_.Length();
    
    char* strbuffer = new char[length1 + length2];
    strcpy(strbuffer, ToCStr());
    
    strcat(strbuffer, o_.ToCStr());
    
    --strhld->instances;
    if (0 == strhld->instances)
    {
        delete strhld;
    }
    
    strhld = new (string_holder);
    strhld->str = strbuffer;
    ++strhld->instances;
    
    return *this;
}

/******INTERNAL FUNCTION DECLARATION******/

/*****FUNCTION DEFINITION******/

bool operator==(const RCString& s1, const RCString& s2)
{
    return !strcmp(s1.ToCStr(), s2.ToCStr());
}

bool operator!=(const RCString& s1, const RCString& s2)
{
    return strcmp(s1.ToCStr(), s2.ToCStr());
}

bool operator<(const RCString& s1, const RCString& s2)
{
    return 0 > strcmp(s1.ToCStr(), s2.ToCStr());
}

bool operator>(const RCString& s1, const RCString& s2)
{
    return 0 < strcmp(s1.ToCStr(), s2.ToCStr());
}

std::ostream& operator<<(std::ostream& os, const RCString& s)
{
    return os << s.ToCStr();
}