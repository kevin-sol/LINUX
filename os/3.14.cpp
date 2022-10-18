#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char **argv)
{
    
    pid_t pid;
    pid = fork();
    if (pid < 0){
        printf("error!\n");
        return 1;
    }
    else if (pid == 0){
        int num=atoi(argv[1]);
        printf("%d\n",num);
        while (num != 1){
            if (num % 2 == 0){
                num = num / 2;
            }
            else{
                num = 3*num + 1;
            }
            printf("%d\n",num);
        }
    }
    else{
        wait(NULL);
        printf("Child Complete!!!\n");
    }
    return 0;
}
