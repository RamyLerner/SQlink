#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "messageQ.h"

int main(){
	char str1[] = "huiiiiiiiiiiiiiiiii";
	char str2[] = "tatatata";
	char* buffer1;
	char* buffer2;
	int size1 = sizeof(str1);
	int size2 = sizeof(str2);
	int fd, fd2, ret;
	
	struct message_t testM1;
	struct message_t testM2;

	testM1.data = str1;
	testM1.size = size1;

	
	testM2.data = str2;
	testM2.size = size2;

	printf("starting\n");
	fd = open("/dev/messageQ5",O_RDWR);
	if(fd<0) {
		fprintf(stderr, "had problems with open\n");
		return 1;
	}

	fd2 = open("/dev/messageQ3",O_RDWR);
	if(fd<0) {
		fprintf(stderr, "had problems with open\n");
		return 1;
	}


	ret = ioctl(fd, WRITE_MSG, &testM1);
	if(ret<0) {
		fprintf(stderr, "had problems with ioctl WRITE_MSG1\n");
		return 1;
	}
	printf("write1 was ok\n");

	ret = ioctl(fd2, WRITE_MSG, &testM2);
	if(ret<0) {
		fprintf(stderr, "had problems with ioctl WRITE_MSG2\n");
		return 1;
	}
	printf("write2 was ok\n");
	
	buffer1 = (char*)malloc(4096);
	ret = ioctl(fd, GET_MSG, buffer1);
	if(ret<0) {
		fprintf(stderr, "had problems with ioctl GET_MSG1\n");
		return 1;
	}
	printf("read1: %s\n",buffer1);

	buffer2 = (char*)malloc(4096);
	ret = ioctl(fd2, GET_MSG, buffer2);
	if(ret<0) {
		fprintf(stderr, "had problems with ioctl GET_MSG2\n");
		return 1;
	}
	printf("read2: %s\n",buffer2);
	
	free(buffer1);
	free(buffer2);
	ret=close(fd);
	if(ret<0) {
		fprintf(stderr, "had problems with close\n");
		return 1;
	}
	return EXIT_SUCCESS;
}
