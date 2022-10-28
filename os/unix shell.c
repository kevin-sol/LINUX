/**
 * Simple shell interface program.
 *
 * Operating System Concepts - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

#define MAX_LINE 80 /* 80 chars per line, per command */

struct queue
{
    char history[100][MAX_LINE];
    int front;
    int rear;
};

int main(void)
{
    char *args[MAX_LINE / 2 + 1]; /* command line (of 80) has max of 40 arguments */
    char input[MAX_LINE];
    int should_run = 1;

    struct queue q;
    q.front=q.rear=0;

    while (should_run)
    {
        printf("osh> ");
        fflush(stdout);
        //
        gets(input);

        if (input[0]=='!')
        {
            if (input[1]=='!')
            {
                strcpy(input,q.history[q.rear-1]);
            }
            else{
                int l=atoi(input+1);
                strcpy(input,q.history[q.front+l-1]);
            }
        }
        

        //history
        if (q.rear-q.front<10)
        {
            strcpy(q.history[q.rear],input);
            q.rear++;
        }
        else
        {
            q.front++;
            strcpy(q.history[q.rear],input);
            q.rear++;
        }
        
        char *p = NULL;
        const char s[2] = " ";
        int i = 0;
        p = strtok(input, s);
        while (p)
        {
            args[i] = p;
            ++i;
            p = strtok(NULL, s);
        }
        //printf("%s\n", args[0]);
        char ex[]="exit";
        if (strcmp(args[0],ex)==0)
        {
            should_run = 0;
            break;
        }
        char *last=args[i-1];
        if (strcmp(last,"&")==0)
        {
            args[i-1]=NULL;
        }
        
        /**
         * After reading user input, the steps are:
         * (1) fork a child process
         * (2) the child process will invoke execvp()
         * (3) if command included &, parent will invoke wait()
         */

        pid_t pid;
        pid = fork(); // fork a child process

        if (pid < 0)
        {
            printf("error");
            exit(-1);
        }
        else if (pid==0)
        {
            //history
            if (strcmp(args[0],"history")==0)
            {
                q.rear--;
                for (int j = q.rear-1; j >= q.front; j--)
                {
                    printf("%d %s\n",j-q.front+1,q.history[j]);
                }
                exit(0);
            }
            
            execvp(args[0], args);//child process invoke execvp()
            exit(0);
        }
        else
        {
            if (strcmp(last,"&")==0)
            {
                continue;
            }
            
            wait(NULL);
        }
    }
    return 0;
}