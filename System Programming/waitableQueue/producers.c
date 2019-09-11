#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include "wQueue.h"
#include "producers.h"

#define MESSAGES_PER_PRODUCER 3

extern wQueue *p2c, *c2p;

static void waitForReply(wQueue* c2p, int tNum, int i){
    char replyBuffer[340];
    wQueueRead (c2p, (void**)&replyBuffer);
    printf("producer no. %d got ack no. %d: %s\n", tNum, i, replyBuffer);
    
}

void* producer(void *tNumPtr) 
{  
    int i;
    int tNum = *(int*)tNumPtr;
    char item[340];
    for (i=0; i<MESSAGES_PER_PRODUCER; i++){
        sprintf(item, "producer no. %d send item no.: %d\n", tNum, i);
        wQueueWrite (p2c, item);
        waitForReply(c2p, tNum, i);
    }
}

int createProducers(pros** prosInst){
    int i;
    int index[NUM_OF_PRODUCERS];
    *prosInst = (pros*)malloc(sizeof(pros));
    if (*prosInst == NULL)
        return -1;
    for (i=0; i<NUM_OF_PRODUCERS; i++){
        index[i]=i;
        if(pthread_create(&((*prosInst)->arr[i]), NULL, producer, &index[i])) {
            fprintf(stderr, "Error creating producer thread\n");
            return -1;
        }
    }
    return 0;
}

int joinProducers(pros* prosInst){
    int i;
    for (i=0; i<NUM_OF_PRODUCERS; i++)
        if(pthread_join(prosInst->arr[i], NULL)) {
            fprintf(stderr, "Error joining producer no. %d\n", i);
            return -1;
        }
    return 0;    
}

void destroyPros(pros* prosInst){
    free(prosInst);
}