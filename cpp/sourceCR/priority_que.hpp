#ifndef ILRD_RD8586_PRIORITYQUEUE_HPP
#define ILRD_RD8586_PRIORITYQUEUE_HPP

/*****************************************************************************
 * API Priority Que
 * Alistair Hudson
 * version 16.08.2020.0
******************************************************************************/

#include <iostream>
#include <queue>
#include <vector>
#include <functional> //std::less

namespace ilrd
{
template <typename T, class Container = std::vector<T>,
  class Compare = std::less<typename Container::value_type> >
class PriorityQueue : private std::priority_queue<T, Container, Compare>
{
public:
    explicit PriorityQueue(const Compare& comp = Compare(),
                         const Container& ctnr = Container());
    /*template <class InputIterator>
    PriorityQueue(InputIterator first, InputIterator last,
                         const Compare& comp = Compare(),
                         const Container& ctnr = Container());*/ //not mandatory (bonus)
    void push (const T& val);
    void pop(void);
    const T& front() const;
    bool empty() const; 

};

template <typename T, class Container, class Compare >
PriorityQueue<T, Container, Compare>::PriorityQueue(const Compare& comp,
                                                    const Container& ctnr)
{

}

template <typename T, class Container, class Compare >
void PriorityQueue<T, Container, Compare>::push (const T& val)
{
    std::priority_queue<T, Container, Compare>::push(val);
}

template <typename T, class Container, class Compare >
void PriorityQueue<T, Container, Compare>::pop(void)
{
    std::priority_queue<T, Container, Compare>::pop();
}

template <typename T, class Container, class Compare >
const T& PriorityQueue<T, Container, Compare>::front() const
{
    return std::priority_queue<T, Container, Compare>::top();
}

template <typename T, class Container, class Compare >
bool PriorityQueue<T, Container, Compare>::empty() const
{
    return std::priority_queue<T, Container, Compare>::empty();
}

}//namespace ilrd

#endif // ILRD_RD8586_PRIORITYQUEUE_HPP