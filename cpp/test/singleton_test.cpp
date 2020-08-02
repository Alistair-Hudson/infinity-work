
#include <list>
#include <iterator>
#include <algorithm>

#include "singleton.hpp"

void Thread(int x)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::list<int>* List = ilrd::Singleton< std::list< int > >::GetInstance();
    List->push_back(x);
    std::cout << List->front() << std::endl;
    /*std::for_each(ilrd::Singleton< std::list< int > >::GetInstance()->begin(),
                    ilrd::Singleton< std::list< int > >::GetInstance()->end(),
                    [](int x) {std::cout << x;});
    std::cout << std::endl;
    */
}

int main()
{
    std::thread t1(Thread, 1);
    std::thread t2(Thread, 2);

    t1.join();
    t2.join();

    ilrd::Singleton< std::list< int > >::CleanUp();

    return 0;
}