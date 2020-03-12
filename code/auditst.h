#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int runaudit(){
 
    int pid2 = fork();

    if(pid2 == -1)
    {
        perror("auditerr: cannot fork");
        printf("errback");
        fflush(stdout);

    } else if( pid2 ==0)
    {
        char *cmdcp = "/bin/auditctl -l -k dem";
        char *args[] = {"auditctl", "-l", " -k", "dem", NULL};

        //out = execvp(cmdcp, args);
        exit(1);
    }
    

    return 0;

}