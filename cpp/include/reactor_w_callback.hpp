//Reactor design pattern API
#include <iostream>
#include <vector>
#include <iterator>
#include <map>
#include <utility>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>

#include "callback.hpp"

//The type of a handle is system specific. We're using UNIX so an handle is represented by an integer
typedef int Handle;

typedef enum MODE
{
    WRITE = 0,
    READ,
    EXCEPTION
};

//The user may derieves from this class to define his own Listener class 
class Listener
{
public:
    Listener(){}
    ~Listener(){}
    void Listen(const std::vector<Handle>& read,
                const std::vector<Handle>& write,
                const std::vector<Handle>& exception);
};

// Registration interface of the Reactor
class Reactor: private boost::noncopyable
{
public:
    Reactor(){}
    void Add( MODE mode, Handle fd, Callback<Source<int>>* callback);
    void Remove( MODE mode, Handle fd);
    void Run();
    void Stop(); // can be called only from the handler/run if there is nothing to listen to (if the map is empty)
    ~Reactor();

private:
    std::map<Handle, Source<int>*> m_read;
    std::map<Handle, Source<int>*> m_write;
    std::map<Handle, Source<int>*> m_exception;
    Listener m_Listener;
};

//An example for a user derieved listener

/* class DerievedListener: public IListener
{
public:

    std::vector<std::pair<IListener::MODE, Handle>> Listen(const std::vector<std::pair<IListener::MODE, Handle>>& handle);
}; */