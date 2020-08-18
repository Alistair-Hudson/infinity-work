

#include "logger.hpp"

using namespace ilrd;

int main()
{
   
    LOG_ERROR("first message");
    sleep(1);
    Singleton<Logger>::CleanUp();
    return 0;
}