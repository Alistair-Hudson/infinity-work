/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

namespace useless
{
unsigned int g_wasteful[400];
extern int g_notthere;
void Foo() {};

namespace wasteoftyme
{
    void Foo() {};
}//namespace wasteoftyme
}//namspace useless

namespace stupid
{
void Foo() {}
void Bar() {}
void DoNothing(unsigned int) {}
}//namespace stupid

namespace useless
{
void DoNothing(int) {}
}//namespace useless

using namespace useless;

void DoStuff()
{
    stupid::Bar();
    using stupid::Foo;
    Foo();
    DoNothing(g_wasteful[3] + 1);
    
}

void Foo () {}

using namespace stupid;

namespace comeon = useless::wasteoftyme;

void DoMoreStuff()
{
    comeon::Foo();
    useless::Foo();
    Bar();
    DoNothing(g_wasteful[3] + 1);
}

namespace useless
{
void DoUselessStuff()
{
    DoNothing(g_wasteful[3] + 1);
}
}//namespace useless


int main()
{
    return 0;
}
