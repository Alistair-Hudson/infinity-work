#include <stdio.h>
#include <stdlib.h>

#include "watchdog.h"

int main()
{
    char dummy[] = "dummy";
    watchdog_t watchdog = WatchdogStart(&dummy, NULL);

    while ( 60 > count)
    {
        sleep(10);
        printf("main program running for %d seconds\n\n", (count*10));
    }
    WatchdogStop(watchdog);
    
    return 0;
}