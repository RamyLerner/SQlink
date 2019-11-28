#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> /*for sleep*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include "messageQ.h"


void* writing_thread(void* fd){
	int ret;
	/*char str1[] = "this is first message";*/
	char* str1 = (char*)malloc(40);
	struct message_t testM;

	strcpy(str1, "this is first message");
	testM.data = str1;
	testM.size = strlen(str1);
	
	fprintf(stdout, "starting writing thread\n");
	sleep (5);
	fprintf(stdout, "writing thread woke up\n");	
	ret = ioctl(*(int*)fd, WRITE_MSG, &testM);
	if(ret<0) {
		fprintf(stderr, "had problems with ioctl WRITE_MSG1\n");
	}
	printf("write1 was ok\n");
}

void* reading_thread(void* fd){
	int ret;
	char* buffer1;
	fprintf(stdout, "starting reading thread\n");	
	buffer1 = (char*)malloc(4096);
	ret = ioctl(*(int*)fd, GET_MSG, buffer1);
	if(ret<0) {
		fprintf(stderr, "had problems with ioctl GET_MSG1\n");
	}
	printf("read1: %s\n",buffer1);
	free(buffer1);
}


int main(){
	
	int fd, ret;
	
	pthread_t t1;
	pthread_t t2;

	fd = open("/dev/messageQ5",O_RDWR);
	if(fd<0) {
		fprintf(stderr, "had problems with open\n");
		return 1;
	}

	ret = pthread_create(&t1, NULL, reading_thread, (void*) &fd);
	if(ret<0) {
		fprintf(stderr, "failed creating reading thread \n");
		return 1;
	}

	ret = pthread_create(&t2, NULL, writing_thread, (void*) &fd);
	if(ret<0) {
		fprintf(stderr, "failed creating writing thread \n");
		return 1;
	}
	
	ret = pthread_join(t1, NULL);
	if(ret<0) {
		fprintf(stderr, "failed joining reading thread \n");
		return 1;
	}
	ret = pthread_join(t2, NULL);
	if(ret<0) {
		fprintf(stderr, "failed joining writing thread \n");
		return 1;
	}
	ret=close(fd);
	if(ret<0) {
		fprintf(stderr, "had problems with close\n");
		return 1;
	}
	return EXIT_SUCCESS;
}
