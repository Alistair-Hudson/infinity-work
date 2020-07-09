#include "reactor.hpp"


class TestListen: public IListener
{
public:
    TestListen(){}
    std::vector<HandleAndMode> Listen(const std::vector<HandleAndMode>& handle);
private:
};


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
    //TestListen listen();
    Reactor reactor();

    reactor.Add(std::make_pair(READ, 4), TestFoo);
    reactor.Add(std::make_pair(READ, 5), TestBar);

    reactor.Run();

    return 0;
}