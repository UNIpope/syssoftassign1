#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/stat.h>
#include <time.h>

#include "lockper.h"
#include "unlockper.h"
#include "backup.h"
#include "transfer.h"
#include "audit.h"
#include "logit.h"


int main ()
{
    time_t now;
    struct tm newyear;
    struct tm newyear2;

    double seconds;
    double seconds2;

    time(&now);  /* get current time; same as: now = time(NULL)  */

    // time for backup 
    newyear = *localtime(&now);
    newyear.tm_hour = 17;
    newyear.tm_min = 16;
    newyear.tm_sec = 0;

    //time for tranfer
    newyear2 = *localtime(&now);
    newyear2.tm_hour = 2;
    newyear2.tm_min = 0;
    newyear2.tm_sec = 0; 


    while(1) {
        sleep(1);
        openlog("websited",LOG_PID|LOG_CONS, LOG_USER);

        time(&now);
        seconds = difftime(now,mktime(&newyear));
        seconds2 = difftime(now,mktime(&newyear2));
        printf("\n%.f", seconds);

        openlog("webd",LOG_PID|LOG_CONS, LOG_USER);
        //backup
        if (seconds == 0) {
            if(runaudit() == 0){               
                syslog(LOG_INFO, "starting auditer");
            }else{
                syslog(LOG_INFO, "auditer start failed");
            }

            syslog(LOG_INFO, "starting 12pm backup and sync");
            if(lockfiles() == 0){
                sleep(5);
                syslog(LOG_INFO, "files have been locked");

                if(runbackup() == 0){
                    syslog(LOG_INFO, "files have been backedup");

                    if(runtransfer() == 0){
                        syslog(LOG_INFO, "files have been synced");

                        if(unlockfiles() == 0){
                            syslog(LOG_INFO, "files have been unlocked");
                            
                            if(logit() == 0){
                                syslog(LOG_INFO, "log file updated");
                            }else{
                                syslog(LOG_INFO, "log file not updated");
                            }

                        }else{
                            syslog(LOG_INFO, "files have not been unlocked");
                        }
                    }else{
                        syslog(LOG_INFO, "files have been not synced");
                    }

                }else{
                    syslog(LOG_INFO, "files have been not backedup");
                }
                
            }else{
                syslog(LOG_INFO, "files were not locked");
            }

            closelog();
        }

        //transfer
        if (seconds2 = 0){;
            if(runtransfer == 0){
                syslog(LOG_INFO, "failed 2am tranfer");
            }else{
                syslog(LOG_INFO, "failed 2am tranfer");
            }
        }
        closelog();
    }

    return 0; 
}