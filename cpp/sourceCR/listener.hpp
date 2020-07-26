/*******************************************************************************
 * File: listener.hpp - header for  listener functions				 		           	  
 * Author: Yurii Yashchuk	                                                      
 * Reviewed by: Dean Oron                       			   
 * Date: 12.7.2020                                                     	       
 ******************************************************************************/

#ifndef __ILRD_RD8586_LISTENER_HPP__
#define __ILRD_RD8586_LISTENER_HPP__

#include <errno.h> // errno 
#include <iostream>
#include "advanced_reactor.hpp"

namespace ilrd
{

	class DerivedListener: public IListener
	{
	public:
	    Listener_Vector Listen(const Listener_Vector &handle)
	    {
		struct timeval tv;
		tv.tv_sec = 7;
		tv.tv_usec = 0;  
		fd_set rset;
		int activity = 0;
		FD_ZERO(&rset);
		Listener_Vector output;

		for (size_t index = 0; index < handle.size(); ++index)
		{
		    FD_SET(handle[index].second, &rset); 
		}


		activity = select(FD_SETSIZE, &rset, NULL, NULL, &tv);

		if ((0 > activity) && (errno!=EINTR))   
		{
		    exit(EXIT_FAILURE);     
		}  

		for (size_t index = 0; index < handle.size(); ++index)
		{
		    if (FD_ISSET(handle[index].second, &rset))
		    {
		        ModeAndHandle new_pair(handle[index].first, handle[index].second);
		        output.push_back(new_pair);
		    }
		}

		return output;
	    }
	};
} // namespace ilrd
#endif /* __ILRD_RD8586_LISTENER_HPP__ */

