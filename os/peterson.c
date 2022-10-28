#include<stdio.h>
#define True 1
#define False 0
int main(int argc, char const *argv[])
{
    int turn;
    int flag[2];

    flag[0] = True;
    turn = 1;
    while(flag[1] && turn == 1);
    //critical section;
    flag[0] = False;
    //remainder section;

    flag[1] = True;
    turn = 0;
    while(flag[0] && turn == 0);
    //critical section;
    flag[1] = False;
    //remainder section;
    return 0;
}

