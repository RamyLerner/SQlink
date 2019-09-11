#ifndef PROD_H
#define PROD_H

    #define NUM_OF_PRODUCERS 10

    typedef struct{
        pthread_t arr[NUM_OF_PRODUCERS];
    } pros;

    void* producer(void *tNumPtr) ;

    int createProducers(pros** prosInst);

    int joinProducers(pros* prosInst);

    void destroyPros(pros* prosInst);

#endif