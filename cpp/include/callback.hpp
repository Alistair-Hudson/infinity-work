#ifndef __CALLBACK_HPP__
#define __CALLBACK_HPP__

/*******************************************************************************
                                * OL85 API FOR CALLBACK
                                * version 09.07.2020.0
******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm> /* find */

/*****CALSSES*****/

template < typename SOURCE >
class Callback;

/*===Source===*/
template < typename T >
class Source : private boost::noncopyable
{
public:
    Source();
    ~Source();
    typedef T dataType; // nested type

    void Subscribe(Callback* callback);
    void Unsubscribe(Callback* callback);
    void Notify(dataType data);

private:
    Callback* m_callback;
};

/*===Callback===*/
template < typename SOURCE >
class Callback : private boost::noncopyable
{
public:
    typedef boost::function< void(SOURCE::dataType) > CallbackPointer;
    typedef boost::function< void() > DeathPointer;

    Callback(const CallbackPointer& func,
             const DeathPointer&
                 death_func); // initialize an empty function for death_func

    ~Callback();

    // should move to the private section
    void Link(SOURCE* source);
    void Unlink(SOURCE* source);
    void Invoke(SOURCE::dataType data);
    // friend SOURCE;

private:
    SOURCE* m_source;
};

/*****METHODS*****/
/*===SOURCE===*/
template <typename T>
Source<T>::Source()
{
    
}

template <typename T>
Source<T>::~Source()
{
    //Unlink callback
}

template <typename T>
void Source<T>::Subscribe(Callback* callback)
{
    //set pointer to callback object
    m_callback = callback;
}

template <typname T>
void Source<T>::Unsubscribe(Callback* callback)
{
    //set callback pointer to NULL
    m_callback = NULL;
}

template <typename T>
void Source<T>::Notify(dataType data)
{
    //send notification to callback
}

/*===CALLBACK===*/
template <typename SOURCE>
Callback<SOURCE>::Callback(const CallbackPointer& func,
                            const DeathPointer&
                            death_func)
{
    
}

template <typename SOURCE>
Callback<SOURCE>::~Callback()
{
    //Unlink source
    Unlink(m_source);
}

template <typename SOURCE>
void Callback<SOURCE>::Link(SOURCE* source)
{
    //Subscribe to source
    source->Subscribe(this);
    //set pointer to source
    m_source = source;
}

template <typename SOURCE>
void Callback<SOURCE>Unlink(SOURCE* source)
{
    //Unsubscribe to source 
    source->Unsubscribe(this);
    //set pointer to NULL
    m_source = NULL;
}

template <typename SOURCE>
void Callback<SOURCE>Invoke(SOURCE::dataType data)
{
    
}

#endif /* __CALLBACK_HPP__ */