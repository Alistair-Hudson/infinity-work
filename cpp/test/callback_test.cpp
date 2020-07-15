/******************************************************************************
 *	Title:		Callback Test
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	13.07.2020.0
 ******************************************************************************/

#include "callback.hpp"

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****STRUCTS*******/

/*****CLASSES******/
class TestObserver
{
public:
    TestObserver();
    ~TestObserver();
    Callback<Source<int>> GetCB() const;

private:
    Callback<Source<int>> callback;
};

class TestSubject
{
public:
    TestSubject();
    ~TestSubject();
    void Sub(Callback<Source<int>>* cb_);
    void Unsub(Callback<Source<int>>* cb_);
    void SendNot(int data);

private:
    Source<int> source;
};

/*****FUNCTORS*****/

/******INTERNAL FUNCTION DECLARATION******/
void Print(int data);

void Death();

/******CLASS METHODS*******/
/*====TestObserver=====*/
TestObserver::TestObserver()
{
   callback(Print, Death);
}

TestObserver::~TestObserver()
{
    ~callback();
}

Callback<Source<int>>& TestObserver::GetCB() const
{
    return &callback;
}

/*======TestSubject=====*/
TestSubject::SendNot(int data)
{
    source.Notify(data);
}

TestSubject::~TestSubject()
{
    ~source();
}

void TestSubject::Sub(Callback<Source<int>> cb_)
{
    source.Subscribe(cb_)
}

void Unsub(Callback<Source<int>> cb_)
{
    source.Unsubscribe(cb_);
}

void SendNot(int data)
{
    source.Notify(data);
}

/******FUNCTIONS*******/

int main()
{
    TestSubject *subject = new TestSubject;
    TestObserver *observer = new TestObserver;

    subject->Sub(observer.GetCB());
    
    subject->SendNot(10);
     
    return 0;
}

void Print(int data)
{
    std::cout << "input is " << data << std::endl;
}

void Death()
{
    std::cout << "I died" << std::endl;
}