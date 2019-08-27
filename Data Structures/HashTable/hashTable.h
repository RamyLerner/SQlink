#ifndef HASH_H
#define HASH_H
#include "destroyFunc.h"

    typedef struct hashTable hashTable;

    enum hashStatus{OK, AllocationError, NullPointerError, KeyNotFound, KeyAlreadyExits};
    typedef enum hashStatus hStatus;

    typedef void* (*elemFunction)(void*, void*);
    typedef int (*elemCompare)(void*, void*);
    typedef unsigned long (*hashFunc)(void*);
    

    hStatus hashCreate(hashTable** ht, int capacity, elemCompare ecFunc, hashFunc hFunc);

    hStatus hashDestroy(hashTable* ht, elemDestroy func);

    hStatus hashFind(hashTable* ht, void* key, void** value);

    hStatus hashInsert(hashTable* ht, void* key, void* value);

    hStatus hashUpdate(hashTable* ht, void* key, void* value);

    hStatus hashRemove(hashTable* ht, void* key, void** value, elemDestroy func);

    hStatus hashForeach(hashTable* ht, elemFunction f, void* context);


#endif