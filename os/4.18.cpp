#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

int desired_amount = 0;
int total_points  = 0;
double X, Y;
double wall_time;
clock_t clock_timer;

int main(){
    printf("Welcome to Threaded Monte Carlo.\n");
    srand(time(NULL));

    do{
        printf("Please enter a positive number for the amount of points you would like to generate? \n");
        scanf("%d", &desired_amount);
    }while (desired_amount <= 0);

    omp_set_num_threads(5);
#pragma omp parallel for
    for (int i=0; i < desired_amount; i++){
        double X = (double)rand() / RAND_MAX; // random numbers 0~1
        double Y = (double)rand() / RAND_MAX;

        if (((X * X) + (Y * Y)) <= 1){
            total_points++;
        }
    }

    double points = 4.0 * total_points;
    double pi = points / desired_amount;
    printf("The approximate value of pi for the desired amount of points %d is: %f \n", desired_amount, pi);
    return 0;
}
