#include<bits/stdc++.h>
int main(int argc, char const *argv[])
{
    pid_t pid;
    pid=fork();
    if (pid<0)
    {
        printf("fail to create child process!!!\n");
    }
    else if (pid==0)
    {
        printf("child pid = %d \n",getpid());
    }
    else
    {
        printf("parent pid = %d\n",getpid());
        sleep(10000);
    }
    return 0;
}
