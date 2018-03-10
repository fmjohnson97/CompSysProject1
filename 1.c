//
//  main.c
//  Project1
//
//  Created by Faith Johnson on 2/28/18.
//  Copyright © 2018 Faith Johnson. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid=fork();
    pid_t pid2=fork();
    int status;
    int retCode;

    if(pid==0 && pid2==0)
    {
        printf("Start D with pid=%d\n",getpid());
        sleep(8);
        //printf("D, my pid=%d, Parent's pid=%d\n",getpid(),getppid());
        printf("Terminate D with pid=%d\n",getpid());
        return 12;
    }
    else if (pid==0)
    {
        printf("Start B with pid=%d\n",getpid());
        printf("Wait for Child D with pid=%d\n", pid2);
        waitpid(pid2,&status,0);
        int retCode=WEXITSTATUS(status);
        printf("\tD's exit code = %d\n",retCode);
        //printf("B, my pid=%d, Parent's pid=%d\n",getpid(),getppid());
        printf("Terminate B with pid=%d\n",getpid());
        return 8;
    }
    else if (pid2==0)
    {
        printf("Start C with pid=%d\n",getpid());
        //printf("C, my pid=%d, Parent's pid=%d\n",getpid(),getppid());
        printf("Terminate C with pid=%d\n",getpid());
        return 9;
    }
    else
    {
        printf("Start A with pid=%d\n",getpid());
        printf("Wait for child C with pid=%d\n",pid2);
        waitpid(pid2,&status,0);
        retCode=WEXITSTATUS(status);
        printf("C's exit code = %d\n",retCode);
        printf("Wait for child B with pid=%d\n", pid);
        waitpid(pid,&status,0);
        retCode=WEXITSTATUS(status);
        printf("\tB's exit code = %d\n",retCode);
        //printf("A, my pid=%d, my exit code=%d\n",getpid(),5);
        printf("Terminate A with pid=%d\n",getpid());
        return 5;
    }
}
