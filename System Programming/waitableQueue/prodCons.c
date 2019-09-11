#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include "wQueue.h"
#include "producers.h"
#include "consumers.h"

#define queueSize 7

wQueue *p2c, *c2p;

int main(){
    pros* prosInst;
    cons* consInst;

    wQueueCreate(&p2c, queueSize);
    wQueueCreate(&c2p, queueSize);

    createProducers(&prosInst);
    createConsumers(&consInst);

    joinProducers(prosInst);
    killConsumers(consInst);

    destroyPros(prosInst);
    destroyCons(consInst);

    wQueueDestroy(p2c);
    wQueueDestroy(c2p);
}