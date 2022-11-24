#include <sys/wait.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> //linux specific library
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h> 
#include <errno.h>
#include <stddef.h>
#include <sys/time.h>
#include <time.h>
#include <sys/syscall.h>
#include <sched.h>

int time1diff,time2diff,time3diff;

int main(){
	pid_t pid1, pid2, pid3;
	pid1 = fork();
	if (pid1 == 0) {
        chdir("/home/vidur/new_kernel/linux_a");
        struct timeval start, end;
        gettimeofday(&start, NULL);
        struct sched_param param;
        param.sched_priority=0;
        int ret = sched_setscheduler(getpid(), SCHED_OTHER, &param);
		char * k[]={"/home/vidur/bkhcod/bs.sh",NULL};
        execvp(k[0],k);
        gettimeofday(&end, NULL);
        int sec1 = (end.tv_sec - start.tv_sec);
        int micro1 = ((sec1 * 1000000) + end.tv_usec) - (start.tv_usec);
        time1diff=micro1;
        FILE * fptr;
        fptr=fopen("ans2.txt","a");
        //fputs("Vidur is good boy",fptr);
        char str[42];
        sprintf(str, "%d", time1diff);
        fputs(str,fptr);
        fputs("\n",fptr);
        fclose(fptr);
	}
	else {
		pid2 = fork();
		if (pid2 == 0) {
            chdir("/home/vidur/new_kernel/linux_b");
            struct timeval start, end;
            gettimeofday(&start, NULL);
            struct sched_param param;
            param.sched_priority=50;
            int ret = sched_setscheduler(getpid(), SCHED_RR, &param);
			char * k[]={"/home/vidur/bkhcod/bs.sh",NULL};
            execvp(k[0],k);
            gettimeofday(&end, NULL);
            int sec1 = (end.tv_sec - start.tv_sec);
            int micro1 = ((sec1 * 1000000) + end.tv_usec) - (start.tv_usec);
            time2diff=micro1;
            FILE * fptr;
            fptr=fopen("ans2.txt","a");
            //fputs("Vidur is good boy",fptr);
            char str[42];
            sprintf(str, "%d", time2diff);
            fputs(str,fptr);
            fputs("\n",fptr);
            fclose(fptr);
		}
		else {
			pid3 = fork();
			if (pid3 == 0) {
                chdir("/home/vidur/new_kernel/linux_c");
                struct timeval start, end;
                gettimeofday(&start, NULL);
                struct sched_param param;
                param.sched_priority=50;
                int ret = sched_setscheduler(getpid(), SCHED_FIFO, &param);
				char * k[]={"/home/vidur/bkhcod/bs.sh",NULL};
                execvp(k[0],k);
                gettimeofday(&end, NULL);
                int sec1 = (end.tv_sec - start.tv_sec);
                int micro1 = ((sec1 * 1000000) + end.tv_usec) - (start.tv_usec);
                time3diff=micro1;
                FILE * fptr;
                fptr=fopen("ans2.txt","a");
                //fputs("Vidur is good boy",fptr);
                char str[42];
                sprintf(str, "%d", time3diff);
                fputs(str,fptr);
                fputs("\n",fptr);
                fclose(fptr);
			}
			else {
				wait(NULL);
			}
		}
	}
	return 0;
}
