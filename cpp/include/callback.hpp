#ifndef __CALLBACK_HPP__
#define __CALLBACK_HPP__

/*******************************************************************************
                                * OL85 API FOR CALLBACK
                                * version 12.07.2020.0
******************************************************************************/
#include <iostream>
#include <assert.h> /* assert */ 

#include <boost/function.hpp> /* function */
#include <boost/core/noncopyable.hpp> /* noncopyable */

#define LOG_ERR(X)      (std::cerr << "ERROR: " <<(X) << std::endl)
#define LOG_WRN(X)      (std::cerr << "WARNING: " <<(X) << std::endl)

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
    typedef T DataType; // nested type

    void Subscribe(Callback<Source<T>>* callback);
    void Unsubscribe(Callback<Source<T>>* callback);
    void Notify(DataType data);

private:
    Callback<Source<T>>* m_callback;
};

/*===Callback===*/
template < typename SOURCE >
class Callback : private boost::noncopyable
{
public:
    typedef boost::function< void (typename SOURCE::DataType) > CallbackPointer;
    typedef boost::function< void() > DeathPointer;


    Callback(const CallbackPointer& func,
             const DeathPointer& death_func = &DefaultDeath);
    ~Callback();

private:
    void Link(SOURCE* source);
    void Unlink(bool has_died = 0);
    void Invoke(typename SOURCE::DataType data);
    static void DefaultDeath(){}

    SOURCE* m_source;
    const CallbackPointer callBackFunction;
    const DeathPointer deathFunction;
    
    friend SOURCE;
};

/*****METHODS*****/
/*===SOURCE===*/
template <typename T>
Source<T>::Source()
{
    m_callback = NULL;
}

template <typename T>
Source<T>::~Source()
{
    //Unlink callback
    if (NULL != m_callback)
    {
        m_callback->Unlink(1);
    }
}

template <typename T>
void Source<T>::Subscribe(Callback<Source<T>>* callback)
{
    assert(NULL != callback); assert(!m_callback);
    //set pointer to callback object
    m_callback = callback;
    m_callback->Link(this);
}

template <typename T>
void Source<T>::Unsubscribe(Callback<Source<T>>* callback)
{
    assert(!m_callback);
    m_callback->Unlink();
    //set callback pointer to NULL
    m_callback = NULL;
}

template <typename T>
void Source<T>::Notify(DataType data)
{
    //send notification to callback
    if (m_callback)
    {
        m_callback->Invoke(data);
    }
    else
    {
        LOG_WRN("No one is subscribed\n");
    }
}

/*===CALLBACK===*/
template <typename SOURCE>
Callback<SOURCE>::Callback(const CallbackPointer& func,
                            const DeathPointer& death_func)
{
    assert(func);
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
    assert(NULL != source); assert(!m_source);
    //set pointer to source
    m_source = source;
}

template <typename SOURCE>
void Callback<SOURCE>::Unlink(bool has_died)
{
    assert(m_source);

    //set pointer to NULL
    m_source = NULL;
    if (has_died)
    {
        deathFunction();
    }
}

template <typename SOURCE>
void Callback<SOURCE>::Invoke(typename SOURCE::DataType data)
{
    //invoke action based on the data
    callBackFunction(data);
}

#endif /* __CALLBACK_HPP__ */