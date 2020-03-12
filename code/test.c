#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/stat.h>
#include <time.h>

#include "backup.h"

int main ()
{
    printf("hello");
    fflush(stdout);

    time_t now;
    double seconds;
    struct tm newyear;

    runbackup();
    /*
    while (1){

        time(&now);
        
        newyear = *localtime(&now);
        newyear.tm_hour = 18;
        newyear.tm_min = 28;
        newyear.tm_sec = 0;

        seconds = difftime(now,mktime(&newyear));
        printf("\n%.f", seconds);
        fflush(stdout);


        


    }
    */
    return 0; 
}