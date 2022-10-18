#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include<wait.h>

int main(int argc, char *argv[])
{
    if (argc!=3)
    {
        printf("error!\n");
    }
    
    char *input = argv[1];
    char *copy = argv[2];
    int fd[2];
    char buf[100];
    char childbuf[100];
    pipe(fd);
    pid_t pid = fork();
    if (pid < 0)
    {
        printf("error!\n");
    }
    else if (pid == 0)
    {
        close(fd[1]);
        ssize_t num_bytes_child =read(fd[0],childbuf,sizeof(childbuf));
        close(fd[0]);
        int targetDesc = open(copy, O_CREAT | O_WRONLY);
        write(targetDesc, childbuf, num_bytes_child);
    }
    else
    {
        close(fd[0]);
        int fileInDesc = open(input, O_RDONLY);
        ssize_t num_bytes = read(fileInDesc, buf, sizeof(buf));
        write(fd[1],buf,num_bytes);
        close(fd[1]);
        wait(NULL);
    }
    
    return 0;
}
