/******************************************************************************
 *	Title:		RC String Numbers
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	02.06.2020.0
 ******************************************************************************/
#include <iostream>     /* std io functions */
#include <string.h>       /* strlen, strcmp */
#include <exception>
#include <cstdlib>

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****STRUCTS*******/
struct string_holder
{
    char* str;
    int instances;
};

/*****CLASSES******/
class RCString
{
private:
    string_holder* strhld;
    
public:
	RCString(const char* str_ = "");
	RCString(const RCString& o_);
	~RCString();
	RCString& operator=(const RCString& o_);
	
	const char* ToCStr() const;
	size_t Length() const;

	char operator[](size_t idx_) const;
	char& operator[](size_t idx_);

	RCString& Concat(const RCString& o_);
	
	

};

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
    return strhld->str[idx_];
}

char& RCString::operator[](size_t idx_)
{
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
bool operator==(const RCString& s1, const RCString& s2);
bool operator!=(const RCString& s1, const RCString& s2);
bool operator<(const RCString& s1, const RCString& s2);
bool operator>(const RCString& s1, const RCString& s2);
std::ostream& operator<<(std::ostream& os, const RCString& s);

/*****FUNCTION DEFINITION******/

int main()
{
   RCString str1 = "Hello ";
   RCString str2(str1);
   RCString str3(str1);
   
   str2 = "world!";
   
   std::cout << "str1 = " << str1.ToCStr() << std::endl;
   std::cout << "str2 = " << str2.ToCStr() << std::endl;
   std::cout << "length of str1 = " << str1.Length() << std::endl;
   std::cout << "character at positon 1 = " << str1[1] << std::endl;
   std::cout << "str1 == str2: " << (str1==str2) << std::endl;
   std::cout << "str1 != str2: " << (str1!=str2) << std::endl;
   std::cout << "str1 < str2: " << (str1<str2) << std::endl;
   std::cout << "str1 > str2: " << (str1>str2) << std::endl;
   
   str1.Concat(str2);
   std::cout << "Concat str1 = " << str1.ToCStr() << std::endl;
   std::cout << "str3 = " << str3 << std::endl;
    return 0;
}

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