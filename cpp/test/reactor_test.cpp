#include "reactor.hpp"


class TestListen: public IListener
{
public:
    TestListen(){}
private:
}


void TestFoo(int fd)
{
    std::cout << "Foo activated" << std::endl;
}

void TestBar(int fd)
{
    std::cout << "Bar activated" << std::endl;
}

int main()
{
    TestListen listen();
    Reactor reactor(listen);

    reactor.Add(make_pair(READ, 4), TestFoo);
    reactor.Add(make_pair(READ, 5), TestBar);

    reactor.Run();

    return 0;
}