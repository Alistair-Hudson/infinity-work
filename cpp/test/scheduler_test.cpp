
#include <iostream>

#include "scheduler.hpp"


void SchedTest1(int fd)
{
    std::cout << "Hello I am a task\n";
}

void SchedTest2(int fd)
{
    std::cout << "Hello I am another Task\n";
}

int main()
{
    Reactor reactor;

    ilrd::Scheduler scd(reactor);

    ilrd::FDTimer::MS firsttime(1000000000);
    ilrd::FDTimer::MS secondtime(2000000000);

    scd.ScheduleAction(firsttime, SchedTest1);
    scd.ScheduleAction(secondtime, SchedTest2);

    reactor.Run();


    return 0;
}