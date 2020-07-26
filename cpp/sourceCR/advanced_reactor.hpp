/*******************************************************************************
 * File: advanced_reactor.hpp - header for advanced reactor functions				 		           	  
 * Author: Yurii Yashchuk	                                                      
 * Reviewed by: Dean Oron                       			   
 * Date: 12.7.2020                                                     	       
 ******************************************************************************/

#ifndef __ILRD_RD8586_ADVANCED_REACTOR_HPP__
#define __ILRD_RD8586_ADVANCED_REACTOR_HPP__
#include <iostream>
#include <vector>
#include <map> 
#include <boost/function.hpp>
#include <utility>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

#include "source_callback.hpp"

namespace ilrd
{
	typedef int Handle;

	enum MODE
	{
		WRITE,
		READ,
		EXCEPTION
	};

	typedef std::pair<MODE, Handle> ModeAndHandle;
	typedef boost::function<void(Handle)> HandleFunc;
	typedef std::vector<ModeAndHandle> Listener_Vector;
	typedef std::map<ModeAndHandle, 
		    boost::shared_ptr< ilrd::Source<Handle> > > Map;

	class IListener
	{
		public:
			virtual ~IListener()
			{}

			virtual Listener_Vector Listen(const Listener_Vector &handle) = 0;
	};


	class Reactor
	{
	public:
		explicit Reactor(IListener *listener): m_Listener(listener), is_running(1){}
		void Add(ModeAndHandle mode_and_handle, Callback<Source <int> > *callback);
		void Remove(ModeAndHandle mode_and_handle);
		void Run();
		void Stop(); // can be called only from the handler/run 
		             // if there is nothing to listen to (if the map is empty)
		~Reactor();

	private:
		Reactor(const Reactor& other);
		Reactor& operator=(const Reactor& other);
		Map m_EventHandlers;
		IListener *m_Listener;
		bool is_running;
	};
} // namespace ilrd
#endif /* __ILRD_RD8586_ADVANCED_REACTOR_HPP__ */
