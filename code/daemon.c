// Orphan Example
// The child process is adopted by init process, when parent process dies.
#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <string.h>

#include "backup.h"

int main()
{
    time_t now;
    struct tm newyear;
    struct tm newyear2;

    double seconds;
    double seconds2;

    time(&now);  /* get current time; same as: now = time(NULL)  */

    // time for backup 
    newyear = *localtime(&now);
    newyear.tm_hour = 18;
    newyear.tm_min = 25;
    newyear.tm_sec = 0;

    //time for tranfer
    newyear = *localtime(&now);
    newyear.tm_hour = 2;
    newyear.tm_min = 0;
    newyear.tm_sec = 0;   

    //paths
    char *intdir = "/srv/int";
    char *livedir = "/srv/live";
    char *backdir = "/home/jack/Documents/dit/yr4/syssoft/ass1/code/testdir";

    // Implementation for Singleton Pattern if desired (Only one instance running)

    // Create a child process
    int pid = fork();

    if (pid > 0) {
        // if PID > 0 :: this is the parent
        // this process performs printf and finishes
        printf("Parent process");
        sleep(10);  // uncomment to wait 10 seconds before process ends
        exit(EXIT_SUCCESS);
    } else if (pid == 0) {
        // Step 1: Create the orphan process
        printf("Child process");

        // Step 2: Elevate the orphan process to session leader, to loose controlling TTY
        // This command runs the process in a new session
        if (setsid() < 0) {
            fprintf(stderr,"SIDfail:%s\n",strerror(errno));
            exit(EXIT_FAILURE); 
        }

        // We could fork here again , just to guarantee that the process is not a session leader
        int pid = fork();
        if (pid > 0) {
            exit(EXIT_SUCCESS);
        } else{

            // Step 3: call umask() to set the file mode creation mask to 0
            // This will allow the daemon to read and write files
            // with the permissions/access required
            umask(0);

            // Step 4: Change the current working dir to root.
            // This will eliminate any issues of running on a mounted drive,
            // that potentially could be removed etc..
            if (chdir("/") < 0 ) {
                fprintf(stderr,"chdirfail:%s\n",strerror(errno));
                exit(EXIT_FAILURE); 
            }

            // Step 5: Close all open file descriptors
            /* Close all open file descriptors */
            int x;
            for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
            {
                close (x);
            }

            // Signal Handler goes here

            // Log file goes here

            // Orphan Logic goes here!!
            // Keep process running with infinite loop
            // When the parent finishes after 10 seconds,
            // the getppid() will return 1 as the parent (init process)

            while(1) {
                sleep(1);
                printf("child 1: my parent is: %i\n", getppid());
                
                time(&now);
                seconds = difftime(now,mktime(&newyear));
                seconds2 = difftime(now,mktime(&newyear2));
                printf("\n%.f", seconds);

                //backup
                if (seconds == 0) {
                    /*
                    char *cmdcp = "/bin/cp";
                    char *args[] = {"cp", "-R", "-f", livedir, backdir, NULL};
                    execvp(cmdcp, args);

                    openlog("webdaesys", LOG_PID|LOG_CONS, LOG_USER);
                    syslog(LOG_INFO, "backuping");
                    closelog;
                    */
                    runbackup();
                    printf("shbfhsf");
                    fflush(stdout);

	            }

                //transfer
                if (seconds2 = 0){
                    char *cmdcp = "/bin/cp";
                    char *args1[] = {"cp", "-R", "-f", intdir, livedir, NULL};
                    execvp(cmdcp, args1);

                }
            }
        }
    }
    
    return 0;
}