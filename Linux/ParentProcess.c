#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/time.h>

char * const env_list[] = {"Hi, my name is ZhangTao!",0};

int main(int argc, char *argv[]){
	pid_t pid;
	struct timeval start, end;
	gettimeofday(&start,NULL);
	if((pid=fork())<0){
		printf("fork error.\n");
		exit(-1);	
	}
	if(pid==0){
		if(execl(argv[1],"Hi, my name is ZhangTao!",0)<0){
			printf("execv() error.\n");
			exit(-1);	
		}	
	}
	wait(0);
	gettimeofday(&end,NULL);
	printf("Son process runs %d.%ds\n",end.tv_sec-start.tv_sec, end.tv_usec-start.tv_usec);
	exit(0);
}
