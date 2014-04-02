#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "sem_functions.h"

#define DELAY_TIME 3

int main(){
	pid_t result;
	int sem_id;
	sem_id = semget(ftok(".",'a'),1,0666|IPC_CREAT);
	init_sem(sem_id,0);
	result=fork();
	if(result==-1){
		perror("Fork\n");
	}
	else if(result == 0){
		printf("Child process will wait for some seconds...\n");
		sleep(DELAY_TIME);
		printf("The returned value is  %d in the child progress(PID=%d)\n",result, getpid());
		printf("the value of semaphore now in child process is %d\n",semctl(sem_id,0,GETVAL,0));
		sem_v(sem_id);  //signal 

	}
	else{
		sem_p(sem_id);  //wait
		printf("The returned value is %d in the parent progress(PID=%d)\n",result, getpid());
		sem_v(sem_id);
		printf("The returned value of semaphore in parent process is %d\n",semctl(sem_id,0,GETVAL,0));
		del_sem(sem_id);
	}
	exit(0);
}

