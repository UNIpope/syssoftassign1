#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int runtransfer(){
    char *livedir = "/srv/live";
    char *intdir = "/srv/int";
 
    int pid2 = fork();

    if(pid2 == -1)
    {
        perror("transfererr: cannot fork");
        printf("errback");
        fflush(stdout);

    } else if( pid2 ==0)
    {
        char *cmdcp = "cp";
        char *args[] = {"cp", "-R", "-f", intdir, livedir, NULL};
        execvp(cmdcp, args);
        exit(1);
    }
    return 0;

}