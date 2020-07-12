#ifndef __CALLBACK_HPP__
#define __CALLBACK_HPP__

/*******************************************************************************
                                * OL85 API FOR CALLBACK
                                * version 12.07.2020.0
******************************************************************************/
#include <iostream>
#include <assert.h> /* assert */
#include <boost/function.hpp> /* function */

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

    void Subscribe(Callback<Source<T>>* callback);
    void Unsubscribe(Callback<Source<T>>* callback);
    void Notify(dataType data);

private:
    Callback<Source<T>>* m_callback;
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
private:
    void Link(SOURCE* source);
    void Unlink(SOURCE* source);
    void Invoke(SOURCE::dataType data);

    SOURCE* m_source;
    CallbackPointer callBackFunction;
    DeathPointer deathFunction;
    
    friend SOURCE;
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
    if (NULL != m_callback)
    {
        m_callback->Unlink(this);
    }
}

template <typename T>
void Source<T>::Subscribe(Callback<Source<T>>* callback)
{
    assert(NULL != callback);
    //set pointer to callback object
    m_callback = callback;
    m_callback->Link(this);
}

template <typename T>
void Source<T>::Unsubscribe(Callback<Source<T>>* callback)
{
    assert(NULL != callback);
    m_callback->Unlink(this);
    //set callback pointer to NULL
    m_callback = NULL;
}

template <typename T>
void Source<T>::Notify(dataType data)
{
    //send notification to callback
    m_callback->Invoke(data);
}

/*===CALLBACK===*/
template <typename SOURCE>
Callback<SOURCE>::Callback(const CallbackPointer& func,
                            const DeathPointer&
                            death_func)
{
    callBackFunction = func;
    deathFunction = death_func;
}

template <typename SOURCE>
Callback<SOURCE>::~Callback()
{
    if (NULL != m_source)
    {
        //Unlink source
        m_source->Unsubscribe(this);
    }
}

template <typename SOURCE>
void Callback<SOURCE>::Link(SOURCE* source)
{
    assert(NULL != source);
    //set pointer to source
    m_source = source;
}

template <typename SOURCE>
void Callback<SOURCE>::Unlink(SOURCE* source)
{
    assert(NULL != source);

    //set pointer to NULL
    m_source = NULL;
}

template <typename SOURCE>
void Callback<SOURCE>::Invoke(SOURCE::dataType data)
{
    //invoke action based on the data
    callBackFunction(data);
}

#endif /* __CALLBACK_HPP__ */