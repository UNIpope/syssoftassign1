#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int logit(){
    int pid2 = fork();

    if(pid2 == -1)
    {
        perror("lockerr: cannot fork");
        printf("errlock");
        fflush(stdout);

    } else if( pid2 ==0)
    {
        char *cmdlk = "/bin/sh";
        char *args[] = {"sh", "/home/jack/Documents/dit/yr4/syssoft/ass1/bashscripts/log.sh", NULL};
        execvp(cmdlk, args);
        exit(1);
    }
    return 0;

}