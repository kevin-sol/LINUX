#include<stdio.h>
#include<stdlib.h>

#define MIN_PID 300
#define MAX_PID 5000

typedef struct PidManager{
    int pid;
    int i;
}pm;
pm*p;

int allocate_map(){
    int i;
    p = (pm*)malloc(sizeof(pm)*(MAX_PID-MIN_PID+1));
    if(p == NULL) return -1;//fail
    p[0].pid = MIN_PID;
    p[0].i = 1;
    for(i = 1; i < MAX_PID - MIN_PID + 1; i++){
        p[i].pid = p[i - 1].pid + 1;
        p[i].i = 1;
    }
    return 1;
}

int allocate_pid(){
    int i ;
    for(i = 0;i < MAX_PID - MIN_PID + 1; i++){
        if(p[i].i == 1){
            p[i].i = 0;
            return p[i].pid;
            }
        }
    return -1;
}

void release_pid(int pid){
    p[pid - MIN_PID].i = 1;
}
int main(int argc, char const *argv[])
{
    allocate_map();
    int pid =allocate_pid();
    printf("pid = %d\n",pid);
    release_pid(pid);
    printf("pid %d had been released\n",pid);
    return 0;
}
