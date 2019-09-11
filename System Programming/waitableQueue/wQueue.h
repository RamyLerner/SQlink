#ifndef WQUEUE_H
#define WQUEUE_H
	
	typedef struct wQueue wQueue;
	
	int wQueueCreate(wQueue** wq, int size);
	
	int wQueueRead (wQueue* wq, void** ptr);
	
	int wQueueWrite (wQueue* wq, void* ptr);
	
	int isEmpty (wQueue* wq);
	
	int isFull (wQueue* wq);
	
	void wQueueDestroy (wQueue* wq);
	
#endif