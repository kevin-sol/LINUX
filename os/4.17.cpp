#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

int Totalnum = 0;
int yuannum  = 0;

void *count(void *args){
    for (int i=0; i < Totalnum; i++){
        double X = (double)rand() / RAND_MAX; // random numbers 0~1
        double Y = (double)rand() / RAND_MAX;
        if (((X * X) + (Y * Y)) <= 1){
            yuannum++;
        }
    }
}

int main(){
    srand(time(NULL));
    pthread_t thread;
    scanf("%d", &Totalnum);
    pthread_create(&thread, NULL, &count, NULL);
    pthread_join(thread, NULL);  // End thread
    double pi = 4.0 * yuannum / Totalnum;
    printf(" %f \n", pi);
    return 0;
}
