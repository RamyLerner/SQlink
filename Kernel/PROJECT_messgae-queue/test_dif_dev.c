#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include "messageQ.h"

#define NUM_READ 20
#define NUM_WRITE 20


struct toThread{
	int fd;
	pthread_mutex_t* printMut;
	int serial;
};

void* writing_thread(void* arg){
	int ret, my_fd;
	char* str1 = (char*)malloc(40);
	struct message_t testM;
	struct toThread* ttp = (struct toThread*)arg;

	sprintf(str1, "message no: %d", ttp->serial);
	testM.data = str1;
	testM.size = strlen(str1);
	my_fd = ttp->fd;
	
	ret = pthread_mutex_lock(ttp->printMut);
	if (ret!=0)
		fprintf(stderr, "reading thread no. %d couldn't lock", ttp->serial);
	ret = ioctl(my_fd, WRITE_MSG, &testM);
	
	
	if(ret<0) {
		fprintf(stderr, "had problems with ioctl WRITE_MSG no. %d\n", ttp->serial);
	}
	else
		printf("write %d was ok\n", ttp->serial);
	
	pthread_mutex_unlock(ttp->printMut);
}

void* reading_thread(void* arg){
	int ret, my_fd;
	char* buffer1;
	struct toThread* ttp = (struct toThread*)arg;
	my_fd = ttp->fd;	
	buffer1 = (char*)malloc(4096);

	ret = pthread_mutex_lock(ttp->printMut);
	if (ret!=0)
		fprintf(stderr, "writing thread no. %d couldn't lock", ttp->serial);
	ret = ioctl(my_fd, GET_MSG, buffer1);
	if(ret<0) {
		fprintf(stderr, "had problems with ioctl GET_MSG1\n");
	}
	
	printf("read no. %d the message: %s\n", ttp->serial, buffer1);
	pthread_mutex_unlock(ttp->printMut);
	free(buffer1);
}

	


int main(int argc, char** args){
	
	int fd, ret, i;

	pthread_t readTh[NUM_READ];
	pthread_t writeTh[NUM_WRITE];

	struct toThread trt[NUM_READ];
	struct toThread twt[NUM_WRITE];
	pthread_mutex_t read_mut;
	pthread_mutex_t write_mut;

	pthread_mutex_init (&read_mut, NULL);
	pthread_mutex_init (&write_mut, NULL);

	fd = open(args[1],O_RDWR);
	if(fd<0) {
		fprintf(stderr, "had problems with open\n");
		return 1;
	}
	
	for (i=0; i<NUM_READ; i++){
		trt[i].serial = i;
		trt[i].fd = fd;
		trt[i].printMut = &read_mut;

		ret = pthread_create(readTh+i, NULL, reading_thread, (void*) (trt+i));
		if(ret<0) {
			fprintf(stderr, "failed creating reading thread no. %d \n", i);
		}
	}

	for (i=0; i<NUM_WRITE; i++){
		twt[i].serial = i;
		twt[i].fd = fd;
		twt[i].printMut = &write_mut;

		ret = pthread_create(writeTh+i, NULL, writing_thread, (void*) (twt+i));
		if(ret<0) {
			fprintf(stderr, "failed creating writing thread no. %d \n", i);
		}
	}
	
	for (i=0; i<NUM_READ; i++){
		ret = pthread_join(readTh[i], NULL);
		if(ret<0) {
			fprintf(stderr, "failed joining reading thread \n");
		return 1;
		}
	}

	for (i=0; i<NUM_WRITE; i++){
		ret = pthread_join(writeTh[i], NULL);
		if(ret<0) {
			fprintf(stderr, "failed joining reading thread \n");
		return 1;
		}
	}
	pthread_mutex_destroy(&read_mut);
	pthread_mutex_destroy(&write_mut);
	ret=close(fd);
	if(ret<0) {
		fprintf(stderr, "had problems with close\n");
		return 1;
	}
	return EXIT_SUCCESS;
}
