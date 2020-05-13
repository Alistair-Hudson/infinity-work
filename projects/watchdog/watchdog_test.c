#include <stdio.h>
#include <stdlib.h>

#include "watchdog.h"

int main(int argc, char** argv)
{
    char dummy[] = "./test";
    int count = 0;
    watchdog_t* watchdog = WatchdogStart(dummy, argv);

    while ( 6 > count)
    {
        sleep(10);
        printf("main program running for %d seconds\n\n", (count*10));
        ++count;
    }
    WatchdogStop(watchdog);
    
    return 0;
}