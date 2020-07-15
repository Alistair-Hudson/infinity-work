//Reactor design pattern API
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <boost/function.hpp>
#include <utility>

#include "callback.hpp"

//The type of a handle is system specific. We're using UNIX so an handle is represented by an integer
typedef int Handle;

enum MODE
{
    WRITE = 0,
    READ,
    EXCEPTION
};

//The user may derieves from this class to define his own Listener class 
class IListener
{
public:
    virtual ~IListener(){}
    virtual void Listen(const std::vector<Handle>& read,
                        const std::vector<Handle>& write,
                        const std::vector<Handle>& exception) = 0;
};

// Registration interface of the Reactor
class Reactor
{
public:
    Reactor(IListener *listener):m_Listener(listener){}
    void Add(Mode mode, Handle fd, Callback<Source<int>>* callback);
    void Remove(MODE mode, Handle fd);
    void Run();
    void Stop(); // can be called only from the handler/run if there is nothing to listen to (if the map is empty)
    ~Reactor();

private:
    Reactor(Reactor&) = delete;
    Reactor& operator= (Reactor&)const = delete;
    std::vector<Source<int>> m_read;
    std::vector<Source<int>> m_write;
    std::vector<Source<int>> m_exception;
    IListener *m_Listener;
};

//An example for a user derieved listener

/* class DerievedListener: public IListener
{
public:

    std::vector<std::pair<IListener::MODE, Handle>> Listen(const std::vector<std::pair<IListener::MODE, Handle>>& handle);
}; */