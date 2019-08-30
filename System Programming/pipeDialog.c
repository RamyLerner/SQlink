#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){
	int pipefd1[2], pipefd2[2], lenSon, lenFather;
	pid_t pid;
	char messageSon[20] = "Hi father", messageFather[20] = "Hi son!", empty[20];
	lenSon = strlen(messageSon);
	lenFather = strlen(messageFather);
	if (pipe(pipefd1) || pipe(pipefd2))
		return 0;
	pid = fork();
	if (pid < 0)
		printf("fork failed\n");
	if (pid == 0){
		write (pipefd1[1], messageSon, lenSon+1);
		read (pipefd2[0], empty, lenFather+1);
		printf("child read: %s\n", empty);
		
	}
	else {
		read (pipefd1[0], empty, lenSon+1);
		printf("parent read: %s\n", empty);
		write (pipefd2[1], messageFather, lenFather+1);
		
			
		
	}
	
	
}