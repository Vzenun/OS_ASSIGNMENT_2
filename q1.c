#include <sys/wait.h>
#include<math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> //linux specific library
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h> //Used for handling directory files
#include <errno.h> //For EXIT codes and error handling
#include <stddef.h>
#include <sys/time.h>

int time1diff,time2diff,time3diff;
int set_priority1=1;
int set_priority2=1;

void countA(){
    unsigned long long int k=pow(2,32);
    unsigned long long int a=0;
    for(int i=0;i<k;i++){
        a++;
    }
    return;
}
void countB(){
    unsigned long long int k=pow(2,32);
    unsigned long long int a=0;
    for(int i=0;i<k;i++){
        a++;
    }
    return;
}
void countC(){
    unsigned long long int k=pow(2,32);
    unsigned long long int a=0;
    for(int i=0;i<k;i++){
        a++;
    }
    return;
}

void * Thr_A(){
    int set_priority=0;
    struct sched_param param;
    param.sched_priority = set_priority;
    int ret = pthread_setschedparam(pthread_self(), SCHED_OTHER, &param);
    struct timeval start, end;
    gettimeofday(&start, NULL);
    countA();
    gettimeofday(&end, NULL);
    int sec1 = (end.tv_sec - start.tv_sec);
    int micro1 = ((sec1 * 1000000) + end.tv_usec) - (start.tv_usec);
    time1diff=micro1;
    return NULL;
}

void * Thr_B(){
    //printf("$$ %d\n",set_priority1);
    struct sched_param param;
    param.sched_priority = set_priority1;
    int ret = pthread_setschedparam(pthread_self(), SCHED_RR, &param);
    struct timeval start, end;
    gettimeofday(&start, NULL);
    countB();
    gettimeofday(&end, NULL);
    int sec1 = (end.tv_sec - start.tv_sec);
    int micro1 = ((sec1 * 1000000) + end.tv_usec) - (start.tv_usec);
    time2diff=micro1;
    set_priority1++;
    return NULL;
}

void * Thr_C(){
    //printf("$ %d\n",set_priority2);
    struct sched_param param;
    param.sched_priority = set_priority2;
    int ret = pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);
    struct timeval start, end;
    gettimeofday(&start, NULL);
    countC();
    gettimeofday(&end, NULL);
    int sec1 = (end.tv_sec - start.tv_sec);
    int micro1 = ((sec1 * 1000000) + end.tv_usec) - (start.tv_usec);
    time3diff=micro1;
    set_priority2++;
    return NULL;
}

int main(){
    for(int i=0;i<10;i++){
        pthread_t thread_1,thread_2,thread_3;
        pthread_create(&thread_1,NULL,&Thr_A,NULL);
        pthread_create(&thread_2,NULL,&Thr_B,NULL);
        pthread_create(&thread_3,NULL,&Thr_C,NULL);
        pthread_join(thread_1,NULL);
        pthread_join(thread_2,NULL);
        pthread_join(thread_3,NULL);
        //printf("%d %d %d",time1diff,time2diff,time3diff);
        FILE * fptr;
        fptr=fopen("ans.txt","a");
        //fputs("Vidur is good boy",fptr);
        char str[42];
        sprintf(str, "%d", time1diff);
        fputs(str,fptr);
        fputs("\n",fptr);
        sprintf(str, "%d", time2diff);
        fputs(str,fptr);
        fputs("\n",fptr);
        sprintf(str, "%d", time3diff);
        fputs(str,fptr);
        fputs("\n",fptr);
        fclose(fptr);
    }
}