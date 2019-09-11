#ifndef CONS_H
#define CONS_H

    #define NUM_OF_CONSUMERS 5

    typedef struct{
        pthread_t arr[NUM_OF_CONSUMERS];
    }cons;

    void* consumer(void* tNumPtr);

    int createConsumers(cons** consInst);

    int killConsumers(cons* consInst);

    void destroyCons(cons* consInst);

#endif