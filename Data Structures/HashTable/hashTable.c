#include <stdlib.h>
#include "hashTable.h"
#include "linkedList.h"
#include "destroyFunc.h"

struct hashTable{
    Node** buckets;
    int size;
    int count;
    elemCompare ecFunc;
    hashFunc hFunc;
};

hStatus hashCreate(hashTable** ht, int capacity, elemCompare ecFunc, hashFunc hFunc){
    Node** buckets;

    *ht = (hashTable*)malloc(sizeof(hashTable));
    if (*ht == NULL)
        return AllocationError;
     
    buckets = (Node**)calloc(capacity * 1.3, sizeof(Node*));
    if (buckets == NULL){
        free(ht);
        return AllocationError;
    }

    (*ht)->buckets = buckets;
    (*ht)->size = capacity * 1.3;
    (*ht)->ecFunc = ecFunc;
    (*ht)->hFunc = hFunc;
    (*ht)->count = 0;
    return OK;
}


hStatus hashDestroy(hashTable* ht, elemDestroy func){
    int i;
    if (ht == NULL) 
        return NullPointerError;
    if (ht->buckets == NULL){
        free(ht);
        return NullPointerError;
    }
    for (i=0; i < ht->size; i++)
        if (ht->buckets[i] != NULL)
            destroyList (ht->buckets[i], func);
    free(ht->buckets);
    free(ht);
    return OK;
}

static hStatus findNode(hashTable* ht, void* key, Node** nd, Node** father){
    unsigned long hushRes;
    Node* scan;
    if (ht == NULL || ht->buckets == NULL)
        return NullPointerError;
    
    hushRes = ht->hFunc(key);
    hushRes %= ht->size;

    *father = NULL;
    scan = ht -> buckets[hushRes];
    while (scan!=NULL){
        if (ht->ecFunc(key, getKey(scan)) == 0){
            *nd = scan;
            return OK;
        }
        *father = scan;
        scan = getNext(scan);
    }
    return KeyNotFound;
}

hStatus hashFind(hashTable* ht, void* key, void** value){
    Node *nd, *father;
    hStatus res;

    if (ht == NULL || ht->buckets == NULL)
        return NullPointerError;
    res = findNode(ht, key, &nd, &father);
    if (res == OK)
        *value = getVal(nd);
    return res;
}


hStatus hashInsert(hashTable* ht, void* key, void* value){
    Node *nd, *father;
    nodeStatus nres;
    unsigned long hushRes;

    if (ht == NULL || ht->buckets == NULL)
        return NullPointerError;
    nres = findNode(ht, key, &nd, &father);
    if (nres == nOK)
        return KeyAlreadyExits;
    hushRes = ht->hFunc(key);
    hushRes %= ht->size;

    nres = addNode ((&ht->buckets[hushRes]), key, value);
    if (nres == nAllocationError)
        return AllocationError;
    ht->count++;
    return OK;
}

hStatus hashUpdate(hashTable* ht, void* key, void* value){
    Node *nd, *father;
    hStatus res;

    if (ht == NULL || ht->buckets == NULL)
        return NullPointerError;
    res = findNode(ht, key, &nd, &father);
    if (res == OK)
        setVal(nd, value);
    return res;
}

hStatus hashRemove(hashTable* ht, void* key, void** value, elemDestroy func){
    Node *nd, *father;
    hStatus res;

    if (ht == NULL || ht->buckets == NULL)
        return NullPointerError;
    res = findNode(ht, key, &nd, &father);
    if (res == OK){
        *value = getVal(nd);
        setNext(father, getNext(nd));
        destroyNode (nd, func);
        ht->count--;
    }
    return res;
}


 hStatus hashForeach(hashTable* ht, elemFunction f, void* context){
     int i;
     Node* list;

     if (ht == NULL || ht->buckets == NULL)
        return NullPointerError;

     for (i=0; i < ht->size; i++){
         list = ht->buckets[i];
         while (list != NULL){
             f(list, context);
             list = getNext(list);
         }
     }

     return OK;
 }