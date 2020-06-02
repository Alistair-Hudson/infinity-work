/******************************************************************************
 *	Title:		Simple String
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	27.05.2020.0
 ******************************************************************************/
#include <iostream> /* std io functions */
#include <string> /* strlen, strcpy, strdup */
#include <exception>
#include <cstdlib>

using namespace std;
/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****STRUCTS*******/
struct BadDog: public runtime_error
{
    BadDog(const string& s_ = "This is a bad dog"): runtime_error(s_) {}
};

/*****CLASSES******/
class X
{
public:
    X() {cout << "X Ctor" << endl;}
    ~X() {cout << "X Dtor" << endl;}
private:
    int m_a;
};

/******CLASS FUNCTIONS*******/

/******INTERNAL FUNCTION DECLARATION******/
void Fifi()
{
    throw BadDog("bad pup"); cerr << "Fifi() after throw" << endl;
}

void Foo()
{
    X x1;
    Fifi();
    cerr << "Foo() after Fifi()" << endl;
}

void Bar()
{
    Foo();
    cerr << "Bar() after Foo()" << endl;
}

/*****FUNCTION DEFINITION******/

int main()
{
    try
    {
        Bar();    
    }
    catch(bad_alloc&)
    {
        cerr << "Out of memory! exciting."; exit(3);
    }
    catch(BadDog& b)
    {
        cerr << "Bad dog exception: " << b.what(); exit(3);
    }
    catch(exception& r)
    {
        cerr << "unknown execption: " << r.what();
        exit(4);
    }
    
    return 0;
}