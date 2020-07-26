////////////////////////////////////////////////////////////////////////////////
// File Name: reacotr.hpp                                                     //
// Author: Lior Cohen                                                         //
// Date 15/07/2020                                                            //
// Purpose: header file for the reactor                                       //
// Code Reviewer: Yurii Yashchuk                                              //
////////////////////////////////////////////////////////////////////////////////

#ifndef ILRD_RD8586_REACTOR_HPP
#define ILRD_RD8586_REACTOR_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <map> 
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <utility>

#include "source_callback.hpp"

using namespace std;

// The type of a handle is system specific.
// We're using UNIX so an handle is represented by an integer
typedef int Handle;

enum MODE
{
    WRITE,
    READ,
    EXCEPTION
};

typedef Source<int> HandleSrc;
typedef Callback<HandleSrc> HandleCallback;
//typedef boost::function<void(int)> HandleFunc;
typedef std::pair<Handle, MODE> HandleAndMode;
typedef std::pair<HandleAndMode, boost::shared_ptr<HandleSrc> > KeyAndSrc;
typedef std::vector<HandleAndMode> VectorHM;

//The user may derive from this class to define his own Listener class
class IListener
{
public:
    virtual ~IListener(){};
    virtual VectorHM Listen(const VectorHM &handle) = 0;
};

// Registration interface of the Reactor
class Reactor
{
public:
    Reactor(IListener *listener) : m_Listener(listener) {}
    void Add(Handle handle, MODE mode, HandleCallback *callback);
    void Remove(Handle handle, MODE mode);
    void Run();
    void Stop();    // can be called only from the handler/run if there is
                    // nothing to listen to (if the map is empty)

    std::map<HandleAndMode, boost::shared_ptr<HandleSrc> > m_EventHandlers;

private:
    IListener *m_Listener;
    bool m_stop;
};


#endif // ILRD_RD8586_REACTOR_HPP
