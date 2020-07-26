/*******************************************************************************
 * File: advanced_reactor.cpp - file for advanced reactor functions	implementation			 		           	  
 * Author: Yurii Yashchuk	                                                      
 * Reviewed by: Dean Oron                       			   
 * Date: 12.7.2020                                                     	       
 ******************************************************************************/

#include "advanced_reactor.hpp"
#include "source_callback.hpp"

using namespace ilrd;

class FillVector
{
    public:
        ModeAndHandle operator()(std::pair<const std::pair<MODE, int>, 
                                 boost::shared_ptr< Source<Handle> > > node)
        {
            return node.first;
        }
};

class RunVector
{
    public:

        RunVector(Map& map)
        :m_handlers(map)
        {}

        void operator()(ModeAndHandle& mode_handle)
        {
            Map::iterator iterator;
            iterator = m_handlers.find(mode_handle);

            if (iterator != m_handlers.end())
            {
                iterator->second->Notify(iterator->first.second);
            }
        }

        private:
            Map m_handlers;
};


void Reactor::Add(ModeAndHandle mode_and_handle, Callback< Source<int> > *callback)
{
	assert(callback);
	assert(m_EventHandlers.end() == m_EventHandlers.find(mode_and_handle)); 

	boost::shared_ptr<Source<Handle> > source = 
		boost::make_shared< Source<Handle> > ();
	source->Subscribe(callback);
	m_EventHandlers.insert(std::pair<ModeAndHandle, 
		boost::shared_ptr< Source<Handle> > >(mode_and_handle, source));
	
}

void Reactor::Remove(ModeAndHandle mode_and_handle)
{
    assert(m_EventHandlers.end() != m_EventHandlers.find(mode_and_handle)); 

    m_EventHandlers[mode_and_handle]->UnSubscribe();

    m_EventHandlers.erase(mode_and_handle);
}

void Reactor::Run()
{
    assert(is_running);

    while (is_running && !m_EventHandlers.empty())
    {
     	Listener_Vector active_vector;

        std::transform(m_EventHandlers.begin(), m_EventHandlers.end(),
            std::back_inserter(active_vector), FillVector());
        Listener_Vector listener_vector = m_Listener->Listen(active_vector);
        
        std::for_each(listener_vector.begin(), listener_vector.end(), 
			RunVector(m_EventHandlers));
    }
}


void Reactor::Stop()
{
    is_running = 0;
}


Reactor::~Reactor()
{
    m_EventHandlers.clear();
}
  


