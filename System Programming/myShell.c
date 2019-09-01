#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

const char* prompt = "-->";

int main(){
	char input[40];
	char* argv[2];
	pid_t pid, waitRes;
	int status;
	argv[1] = NULL;
	while (strcmp(input, "exit")){
		printf("%s", prompt);
		scanf("%s", input);
		/*if (strcmp (input, "\n"))
			continue;*/
		argv[0] = input;
		pid = fork();
		if (pid < 0){
			printf("fork error\n");
		}
		else if (pid == 0){
			execv(input, argv);
		}
		else{
			waitRes = wait(&status); /* wait for child */
			if (waitRes != pid)       
        			printf("wait error\n");
    		}
		
	}
}
