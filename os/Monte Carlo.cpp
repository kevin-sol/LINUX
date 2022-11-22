#include <stdio.h>
#include <stdlib.h>
#ifndef __USE_GNU
#define __USE_GNU
#endif // !__USE_GNU
#include <unistd.h>
#include <sched.h>
#include <pthread.h>
#include <semaphore.h>

double PI = 3.1415926535898;	//标准PI值

//全局变量
int sum_dots = 1000000;	//点的总数
int sum_in_circle = 0;	//在圆内的点的总数

//声明锁
pthread_mutex_t lock_sum;
pthread_mutex_t lock_in;

//判断点是否在圆内
int inCircle(double x, double y) {
    return (x * x + y * y) <= 1.0?1:0;
}


void* runner1(void *args) {
	double x, y;	//随机点坐标
	while (1){
		pthread_mutex_lock(&lock_sum);	//判断前，对点总数上锁
		if (sum_dots > 0) {
			sum_dots--;
			pthread_mutex_unlock(&lock_sum);

			//生成随机点 [-1,1]
			x = 2.0 * rand() / (double)RAND_MAX - 1;
			y = 2.0 * rand() / (double)RAND_MAX - 1;

			//如果生成点在圆中，圆内点总数+1
			if (inCircle(x, y)) {
				pthread_mutex_lock(&lock_in);
				sum_in_circle++;
				pthread_mutex_unlock(&lock_in);
			}
		}
		else {
			pthread_mutex_unlock(&lock_sum);
			break;
		}		
	}
	pthread_exit(NULL);	//退出线程
}


int main(){
	scanf("%d",&sum_dots);
	int sum_dots_p = sum_dots;	//复制总点数，作最后计算用
	pthread_t tid1, tid2;		//线程ID
	pthread_attr_t attr;		//线程属性
	pthread_attr_init(&attr);	//设置默认线程属性

	//初始化随机数发生器 
	srand(1);

	//初始化锁
	pthread_mutex_init(&lock_sum, NULL);
	pthread_mutex_init(&lock_in, NULL);

	//执行两个线程分别进行随机生成点
	pthread_create(&tid1, &attr, runner1, NULL);
	pthread_create(&tid2, &attr, runner1, NULL);

	//等待两个线程
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	//计算结果
	double estimate_PI = (double)(4.0 * sum_in_circle / sum_dots_p);
	printf("PI: %lf\n", estimate_PI);
	printf("Error Value: %lf\n", estimate_PI - PI);

	return 0;
} 

