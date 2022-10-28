#include<stdio.h>
#include<stdlib.h>
#include <pthread.h>
#include <time.h>
#include <omp.h>
#include <unistd.h>

#define MIN_PID 300
#define MAX_PID 5000

//pthread_mutex_t mutex;
int threadVar = 0;


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

void *threadCall(void* args)                         
{
    if (args==NULL)
    {
        printf("NULL\n");//fail to create
    }
    
    int ret = allocate_pid();       
    printf("%d %d\n",threadVar++, ret);
    sleep(rand());
    release_pid(ret);
    return NULL;
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    int pid;
    allocate_map();
    pthread_t thread[100];
    printf("Thread values:\n");
    omp_set_num_threads(4);
    #pragma omp parallel for
    for (int i = 0; i < 100; i++)
    {
        pthread_create(&thread[i],NULL,&threadCall,NULL);
    }
    
    return 0;
}