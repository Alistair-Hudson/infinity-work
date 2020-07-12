#ifndef __OBSERVER_HPP__
#define __OBSERVER_HPP__

/*******************************************************************************
                                * OL85 API FOR OBSERVER
                                * version 09.07.2020.0
******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm> /* find */

template<typename T>
class ASubject;

template<typename T>
class IObserver
{
public:
    virtual IObserver(ASubject<T>& subject):m_subject(subject)
    {
        m_subject->Attach(this);
    }
    virtual ~IObserver()
    {
        m_subject->Detach(this);
    }
    virtual void Update(T* arg) = 0;
protected:
    ASubject<T>& m_subject;
private:

};

template<typename T>
class ASubject
{
public:
    virtual ~ASubject(){}
    virtual void Attach(IObserver<T>* observer);
    virtual void Detach(IObserver<T>* observer);
protected:
    virtual void Notify() = 0;
    std::vector<IObserver<T>*> m_observerList;
private:
    
};

template<typename T>
void ASubject<T>::Attach(IObserver<T>* observer)
{
    m_observerList.push_back(observer);
}

template<typename T>
void ASubject<T>::Detach(IObserver<T>* observer)
{
     m_observerList.erase(find(m_observerList.begin(), m_observerList.end(), observer));
}


#endif /* __OBSERVER_HPP__ */