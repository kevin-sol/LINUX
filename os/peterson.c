#include<stdio.h>
#include<pthread.h>

#define True 1
#define False 0

int turn;
int flag[2]={False};

void *fun0(void *args)
{

    flag[0] = True;
    turn = 1;
    while(flag[1]==True && turn == 1){
        printf("fun0 is waiting\n");
    }
    //critical section;
    printf("fun0 is in critical section\n");
    flag[0] = False;
    //remainder section;
}
void *fun1(void *args)
{
    flag[1] = True;
    turn = 0;
    while(flag[0]==True && turn == 0)
    {
        printf("fun1 is waiting\n");
    }
    //critical section;
    printf("fun1 is in critical section\n");
    flag[1] = False;
    //remainder section;
}
int main(int argc, char const *argv[])
{
    pthread_t td[2];
    pthread_create(&td[0],NULL,fun0,NULL);
    pthread_create(&td[1],NULL,fun1,NULL);
    for (int i = 0; i < 2; i++)
    {
        pthread_join(td[i],NULL);
    }
    return 0;
}


