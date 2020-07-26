/*******************************************************************************
 * File: source_callback.hpp - header for  source_callback functions				 		           	  
 * Author: Yurii Yashchuk	                                                      
 * Reviewed by: Dean Oron                       			   
 * Date: 12.7.2020                                                     	       
 ******************************************************************************/

#ifndef ILRD_RD8586_SOURCE_CALLBACK_HPP
#define ILRD_RD8586_SOURCE_CALLBACK_HPP
#include <iostream>
#include <utility>
#include <cassert>
#include <boost/function.hpp>
#include <boost/core/noncopyable.hpp>


#define LOG_ERR(X)  (std::cerr << "ERROR: " << (X) << std::endl)
#define LOG_WRN(X)  (std::cerr << "WARNING: " << (X) << std::endl)

namespace ilrd
{

    template <class SOURCE>
    class Callback;

    template <class T>
    class Source: private boost::noncopyable
    {
    public:
        Source();
        ~Source();
        typedef T dataType; //nested  type
        void Subscribe(Callback <Source <T> >* call);
        void UnSubscribe();  
        void Notify(dataType data) ;
    private:
        Callback<Source <T> >* m_callback;
    };

    template <class SOURCE>
    class Callback: private boost::noncopyable
    {
    public:
        typedef boost::function <void (typename SOURCE::dataType) > NotifyFunction;
        typedef boost::function <void () > NotifyDeath;

        Callback(const NotifyFunction& function,
                const NotifyDeath& death_function = &DummyFunction);
        ~Callback();
    private:
        struct FriendHelper {typedef SOURCE MySource;};
        friend class FriendHelper::MySource;

        SOURCE *m_source;
        const NotifyFunction m_function;
        const NotifyDeath m_death_function;

        void Link(SOURCE* source);
        void UnLink(bool has_died);
        void Invoke(typename SOURCE::dataType data);
    	static void DummyFunction(){}
    };


    //                         CLASSES DEFINITIONS                                

	template<class T> 
	Source<T>::Source()
	{
        m_callback = NULL;
	}

    template <class T>
    Source<T>::~Source()
    {
		if (m_callback)
		{
		    m_callback->UnLink(true);
		}
    }

    template <class T>
    void Source<T>::Subscribe(Callback< Source<T> >* call)
    {
		if (!call)
		{
		    LOG_ERR("callback not exist");
		}
		else
		{
		    m_callback = call;
		    m_callback->Link(this);
		}    
    }

    template <class T>
    void Source<T>::UnSubscribe()
    {
		if (m_callback)
		{
		    m_callback->UnLink(false);
		    m_callback = NULL;
		}
    }

    template <class T>
    void Source<T>::Notify(dataType data)
    {
	    if (m_callback)
	    {
			m_callback->Invoke(data);
	    }
        else
        {
            LOG_WRN("callback not exist");
        }
        
    }


    template<class SOURCE>
    Callback<SOURCE>::Callback(const NotifyFunction& function,
                const NotifyDeath& death_function) :
        m_source(NULL), m_function(function) , m_death_function (death_function)
    {
        assert(!m_function.empty());
    }


    template <class SOURCE>
    Callback<SOURCE>::~Callback()
    {
		if (m_source)
		{
		    m_source->UnSubscribe();
		}

		if (m_death_function)
		{
		    m_death_function();
		}
    }


    template <class SOURCE>
    void Callback<SOURCE>::Link(SOURCE* source)
    {
        assert(!m_source);
        assert(source);
            
        m_source = source;
    }

	template<class SOURCE> 
	void Callback<SOURCE>::UnLink(bool has_died)
	{
		assert(m_source);

		m_source = NULL;

		if (has_died)
		{
		    m_death_function();
		}
	}


	template<class SOURCE> 
	void Callback<SOURCE>::Invoke(typename SOURCE::dataType data)
	{
		assert(m_function);

		m_function(data);
	}

}//namespace ilrd
#endif // ILRD_RD8586_SOURCE_CALLBACK_HPP




