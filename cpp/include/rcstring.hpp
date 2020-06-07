#ifndef __OL85_RCSTRING_HPP__
#define __OL85_RCSTRING_HPP__

/*******************************************************************************
                                * OL85 API FOR RCSTRING
                                * version 04.06.2020.0
******************************************************************************/
#include <iostream>

struct string_holder
{
    char* str;
    int instances;
};

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

bool operator==(const RCString& s1, const RCString& s2);

bool operator!=(const RCString& s1, const RCString& s2);

bool operator<(const RCString& s1, const RCString& s2);

bool operator>(const RCString& s1, const RCString& s2);

std::ostream& operator<<(std::ostream& os, const RCString& s);

#endif /* __OL85_RCSTRING_HPP__ */