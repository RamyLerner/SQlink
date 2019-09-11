#include "wQueue.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

struct wQueue{
	void** arr;
	int size;
	int head; /*first element to read*/
	int tail; /*first empty place to write*/
	int numberOfElements;
	sem_t semE;
	sem_t semF;
	pthread_mutex_t mut;
	};

int wQueueCreate(wQueue** wq, int size){
	sem_t semE, semF;
	pthread_mutex_t mut;
	
	sem_init (&semE, 0, size);
	sem_init (&semF, 0, 0);
	
	*wq = (wQueue*)malloc(sizeof(wQueue));
	if (!wq)
		return 1;
		
	(*wq)->arr = malloc(size * sizeof(void*));
	if (!(*wq)->arr)
		return 1;
		
	if (pthread_mutex_init(&mut, NULL) != 0)
        	return 1;

	(*wq)->size = size;
	(*wq)->head = 0;
	(*wq)->tail = 0;
	(*wq)->numberOfElements = 0;
	(*wq)->semE = semE;
	(*wq)->semF = semF;
	(*wq)->mut = mut;
	
	return 0;
}


int wQueueRead (wQueue* wq, void** buffer){
	if (!wq || !buffer)
		return 1;
		
	sem_wait(&wq->semF);
    pthread_mutex_lock (&wq->mut);

	*buffer = wq->arr[wq->head];
	wq->head = (wq->head + 1) % wq->size;

	pthread_mutex_unlock(&wq->mut);
    sem_post(&wq->semE);

	return 0;
}

int wQueueWrite (wQueue* wq, void* ptr){
	if (!wq || !ptr)
		return 1;

	sem_wait(&wq->semE);
    pthread_mutex_lock (&wq->mut);
        
	wq->arr[wq->tail] = ptr;
	wq->tail = (wq->tail + 1) % wq->size;

	pthread_mutex_unlock(&wq->mut);
    sem_post(&wq->semF);

	return 0;
}

void wQueueDestroy (wQueue* wq){
	int i;
	if (wq != NULL && wq->arr != NULL){
		sem_close(&wq->semE);
		sem_close(&wq->semF);
		pthread_mutex_destroy(&wq->mut);
		/*for (i=0; i < wq->size; i++)
			free (wq->arr[i]);*/
		free(wq->arr);
	}1	
	free (wq);

}