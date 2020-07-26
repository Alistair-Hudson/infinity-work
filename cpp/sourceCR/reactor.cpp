////////////////////////////////////////////////////////////////////////////////
// File Name: reacotr.cpp                                                     //
// Author: Lior Cohen                                                         //
// Date 15/07/2020                                                            //
// Purpose: functions file for the reactor                                    //
// Code Reviewer: Yurii Yashchuk                                              //
////////////////////////////////////////////////////////////////////////////////

#include "reactor.hpp"

void Reactor::Add(Handle handle, MODE mode, HandleCallback *callback)
{
    std::map<HandleAndMode, boost::shared_ptr<HandleSrc> >::iterator iter;

    iter = m_EventHandlers.find(HandleAndMode(handle, mode));

    if (iter != m_EventHandlers.end())
    {
        iter->second->Subscribe(callback);

        return;
    }
    
    boost::shared_ptr<HandleSrc> src(new HandleSrc);
    src->Subscribe(callback);

    m_EventHandlers.insert(KeyAndSrc(HandleAndMode(handle, mode), src));
}

void Reactor::Remove(Handle handle, MODE mode)
{
    std::map<HandleAndMode, boost::shared_ptr<HandleSrc> >::iterator iter;
    HandleAndMode key(handle, mode);

    iter = m_EventHandlers.find(key);

    if (iter != m_EventHandlers.end())
    {
        m_EventHandlers.erase(key);
    }

    if (0 == m_EventHandlers.size())
    {
        m_stop = 1;
    }
}

void Reactor::Run()
{
    // As long as the map isn't empty
    if (0 != m_EventHandlers.size())
    {
        m_stop = 0;
    }

    std::map<HandleAndMode, boost::shared_ptr<HandleSrc> >::iterator iter;
    VectorHM all_handles;

    // Filling the all_handles vector with handels
    for (iter = m_EventHandlers.begin(); iter != m_EventHandlers.end(); ++iter)
    {
        all_handles.push_back(iter->first);
    }

    // Will run until stop changes to 1
    while (!m_stop)
    {
        VectorHM ready_handles = m_Listener->Listen(all_handles);

        for (VectorHM::iterator v_iter = ready_handles.begin();
                                        v_iter != ready_handles.end(); ++v_iter) 
        { 
            cout << "check before function call" << endl;
            m_EventHandlers[*v_iter]->Notify((*v_iter).second);

            // Preventing function callback running after Stop() function
            if (!m_stop)
            {
                break;
            }
        }
    }
}

void Reactor::Stop()
{
    m_stop = 1;
}