#include <iostream>

#include "priority_que.hpp"

int main()
{
    ilrd::PriorityQueue<int> pque;


    std::cout << pque.empty() << std::endl;

    pque.push(2);
    std::cout << pque.empty() << std::endl;
    std::cout << "front = " << pque.front() << std::endl;

    pque.push(4);
    std::cout << "front = " << pque.front() << std::endl;

    pque.pop();
    std::cout << "front = " << pque.front() << std::endl;


    return 0;
}