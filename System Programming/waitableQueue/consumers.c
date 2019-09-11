#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include "wQueue.h"
#include "consumers.h"

extern wQueue *p2c, *c2p;

static void sendAck(wQueue* c2p, int tNUM){
    char ackMesssage[340];
    sprintf(ackMesssage, "consumer no. %d got it!", tNUM);
    wQueueWrite (c2p, (void*)ackMesssage);
}

static void consumeItem(int tNum, char* buffer){
    printf("concumer no. %d read: %s\n", tNum, buffer);
}

void* consumer(void* tNumPtr) 
{
    int tNum = *(int*)tNumPtr;
    char buffer[340];
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    while(1){
        wQueueRead (p2c, (void**)&buffer);
        consumeItem(tNum, buffer);
        sendAck(c2p, tNum);
    }
}

int createConsumers(cons** consInst){
    int i;
    int index[NUM_OF_CONSUMERS];
    *consInst = (cons*)malloc(sizeof(cons));
    if (*consInst == NULL)
        return -1;
    for (i=0; i<NUM_OF_CONSUMERS; i++){
        index[i]=i;
        if(pthread_create(&((*consInst)->arr[i]), NULL, consumer, & index[i])) {
            fprintf(stderr, "Error creating consumer thread\n");
            return -1;
        }
    }
    return 0;
}

int killConsumers(cons* consInst){
    int i;
    for (i=0; i<NUM_OF_CONSUMERS; i++)
        if(pthread_cancel(consInst->arr[i])) {
            fprintf(stderr, "Error canceling consumer no. %d\n", i);
            return -1;
        }
    return 0;    
}

void destroyCons(cons* consInst){
    free(consInst);
}

