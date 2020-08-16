/*****************************************************************************/
/*                     TEST WQUEUE                                      */
/*****************************************************************************/
#include <pthread.h> //threads
#include <iostream> // ostream
#include <queue>    // queue
#include <unistd.h>//sleep
#include <fstream>      // std::ofstream
#include <boost/thread/thread.hpp>//boost::threads
#include "waittable.hpp" // singleton implementation

using namespace ilrd; 

struct PushThread
{
    PushThread(WaitableQueue<std::queue<int>, int >& queue, int & i) :m_queue(queue),m_i(i) { }
    void operator()()
    {
        std::cout << "Push" << std::endl;
        sleep(1);
        m_queue.Push(m_i);
    }
private:
    WaitableQueue<std::queue<int>, int>& m_queue;
     int & m_i;
};
//functor
struct PopThread
{
    PopThread(WaitableQueue<std::queue<int>, int >& queue, int & i) :m_queue(queue), m_i(i) { }
    void operator()()
    {
        std::cout << "Pop..."
        <<m_queue.Pop(m_i, WaitableQueue<std::queue<int>, int >::Millisec(1000)) << std::endl;
    }
private:
    int & m_i;
    WaitableQueue<std::queue<int>, int >& m_queue;
};

static void FillArray(int * array, size_t size)
{
    int i = 0;
    for(i = 0; i < size; i++)
    {
        array[i] = i;
    }
}

/*****************************************************************************/
/*                     MAIN                                                   */
/*****************************************************************************/

const int NUM_THREADS = 16;

const int NUM_READ = NUM_THREADS/2;
const int NUM_WRITE = NUM_THREADS-NUM_READ;

int main() 
{ 
    int array[NUM_THREADS] ={0};
    FillArray(array, NUM_THREADS);
    WaitableQueue<std::queue<int>, int > my_queue;

    boost::thread threads[NUM_THREADS];


    size_t i = 0;

    for (i = 0; i < NUM_READ; i++)
    {
        threads[i] = boost::thread(PopThread(my_queue,array[i]));
    }

    for (; i < NUM_THREADS; i++)
    {
        threads[i] = boost::thread(PushThread(my_queue, array[i]));  
    }

    for (i = 0; i < NUM_THREADS; i++)
    {
       threads[i].join(); 
    }

    return 0;
}