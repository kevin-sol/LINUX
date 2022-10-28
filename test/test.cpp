#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <unistd.h>
#define MIN_PID 300
#define MAX_PID 5000
#define TRUE 1
#define FALSE 0
pthread_mutex_t mutex;
int threadVar = 0;
 
struct PidTable{
    int pid;
    int isAvailable;
}*PID;
 
int allocate_map(){
    int i;
    PID = (struct PidTable*)calloc((MAX_PID - MIN_PID + 1), sizeof(struct PidTable));
    if(PID == NULL) return -1;
    PID[0].pid = MIN_PID;
    PID[0].isAvailable = TRUE;
    for(i = 1; i < MAX_PID - MIN_PID + 1; i++){
        PID[i].pid = PID[i - 1].pid + 1;
        PID[i].isAvailable = TRUE;
    }
    return 1;
}
 
int allocate_pid(){
    int i ;
    for(i = 0;i < MAX_PID - MIN_PID + 1; i++){
        if(PID[i].isAvailable == TRUE){
            PID[i].isAvailable = FALSE;
            return PID[i].pid;
        }
    }
    if(i == MAX_PID - MIN_PID + 1)
        return -1;
    else
        return 0;
}
 
void release_pid(int pid){
    PID[pid - MIN_PID].isAvailable = TRUE;
}

void *threadCall(void* X)                         
{
    int ret = allocate_pid();       
    printf("%d %d\n",threadVar++, ret);
    sleep(rand());
    release_pid(ret);
}
int main()
{
    srand(time(NULL));
    int pid;
    allocate_map();
    pthread_t thread[100];
    printf("Every thread will print the value of pid and increment it by 1.\n");
    omp_set_num_threads(5);
    #pragma omp parallel for
    for(int i = 0; i < 100; i++){
        pthread_create(&thread[i], NULL, &threadCall, NULL);
    }
    return 0;
}