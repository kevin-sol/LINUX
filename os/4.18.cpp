#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

int Totalnum = 0;
int yuannum  = 0;
double X, Y;

int main(){
    srand(time(NULL));
    scanf("%d", &Totalnum);
    omp_set_num_threads(4);
    #pragma omp parallel for
    for (int i=0; i < Totalnum; i++){
        double X = (double)rand() / RAND_MAX; // random numbers 0~1
        double Y = (double)rand() / RAND_MAX;
        if (((X * X) + (Y * Y)) <= 1){
            yuannum++;
        }
    }
    double pi = 4.0 * yuannum / Totalnum;
    printf(" %f \n", pi);
    return 0;
}
