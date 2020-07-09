//Reactor design pattern API
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <boost/function.hpp>
#include <utility>

//The type of a handle is system specific. We're using UNIX so an handle is represented by an integer
typedef int Handle;

enum MODE
{
    WRITE = 0,
    READ,
    EXCEPTION
};

typedef boost::function< void(int) > HandleFunc;
typedef std::pair<MODE, Handle> HandleAndMode;

//The user may derieves from this class to define his own Listener class 
class IListener
{
public:
    virtual ~IListener(){}
    virtual std::vector<HandleAndMode> Listen(const std::vector<HandleAndMode>& handle); // = 0;
};

// Registration interface of the Reactor
class Reactor
{
public:
    Reactor(IListener *listener):m_Listener(listener){}
    void Add(HandleAndMode handle_and_mode, HandleFunc func);
    void Remove(HandleAndMode handle_and_mode);
    void Run();
    void Stop(); // can be called only from the handler/run if there is nothing to listen to (if the map is empty)
    ~Reactor();

private:
    Reactor(Reactor&) = delete;
    Reactor& operator= (Reactor&)const = delete;
    std::map<HandleAndMode, HandleFunc> m_EventHandlers;
    IListener *m_Listener;
};

//An example for a user derieved listener

/* class DerievedListener: public IListener
{
public:

    std::vector<std::pair<IListener::MODE, Handle>> Listen(const std::vector<std::pair<IListener::MODE, Handle>>& handle);
}; */