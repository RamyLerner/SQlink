#include <stdlib.h>
#include <unistd.h> /*for sleep, fork, wait, execl*/
#include <sys/types.h>
#include <sys/stat.h>
/*#include "messageQ.h"*/

#define NUM_PROC 5


int main(){
	
	int i;
	pid_t pid;
	for (i=0; i<NUM_PROC; i++){
		pid = fork();
		if (pid == 0)
			execl("./test_lock_thread", "./test_lock_thread", (char*)NULL);
	}
	sleep(5);
	for (i=0; i<NUM_PROC; i++)
		wait(NULL);
	return EXIT_SUCCESS;
}
