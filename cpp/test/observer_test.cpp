/******************************************************************************
 *	Title:		Observer Test
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	09.06.2020.0
 ******************************************************************************/

#include "observer.hpp"

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/
static int g_oid = 0;

/*****STRUCTS*******/

/*****CLASSES******/
class TestObserver: public IObserver<int>
{
public:
    TestObserver(ASubject<int>& subject):m_subject(subject), m_id(++g_oid)
    {
        subject.Attach(this);
    }
    void Update(int* arg);
    int GetID()const{return m_id;}
    int GetX()const{return m_x;}

private:
    int m_id;
    int m_x;
     ASubject<int>& m_subject;
};

class TestSubject: public ASubject<int>
{
public:
    TestSubject():m_x(0){}
    ~TestSubject(){m_observerList.clear();}
    void Notify();
private:
    int m_x;
};

/*****FUNCTORS*****/
class UpdateFunctor
{
public:
    UpdateFunctor(int x_):x(x_){}
    void operator() (TestObserver& observer)
    {
        observer.Update(&x);
    }

private:
    int x;
};

/******CLASS METHODS*******/
/*====TestObserver=====*/
void TestObserver::Update(int* arg)
{
    m_x = *arg;
    std::cout << "Observer ID:" << m_id << " out = " << m_x << std::endl;
}

/*======TestSubject=====*/
void TestSubject::Notify()
{
    int x = 10;
    std::vector<IObserver<int> *>::iterator iterator = m_observerList.begin();
    while (iterator != m_observerList.end()) 
    {
      (*iterator)->Update(&x);
      ++iterator;
    }
}
/******INTERNAL FUNCTION DECLARATION******/

/******FUNCTIONS*******/

int main()
{
    TestSubject *subject = new TestSubject;
    TestObserver *observer1 = new TestObserver(*subject);
    TestObserver *observer2 = new TestObserver(*subject);
    TestObserver *observer3 = new TestObserver(*subject);

    
    subject->Notify();
    
    subject->Detach(observer2);
    subject->Notify();

    delete observer3;
    delete observer2;
    delete observer1;
    delete subject;
     
    return 0;
}