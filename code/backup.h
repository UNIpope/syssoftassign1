#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int runbackup(){
    char *livedir = "/srv/live";
    char *backdir = "/srv/back";
 
    int pid2 = fork();

    if(pid2 == -1)
    {
        perror("backuperr: cannot fork");
        printf("errback");
        fflush(stdout);

    } else if( pid2 ==0)
    {
        char *cmdcp = "/bin/cp";
        char *args[] = {"cp", "-R", "-f", livedir, backdir, NULL};
        execvp(cmdcp, args);
        exit(1);
    }
    return 0;

}