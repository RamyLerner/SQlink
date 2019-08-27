#ifndef NODE_H
#define NODE_H
#include "destroyFunc.h"


    typedef struct Node Node;
    enum nodeStatus{nOK, nAllocationError, nNullPointerError};
    typedef enum nodeStatus nodeStatus;

    typedef void (*printFunc)(void*, void*);

    nodeStatus createNode(Node** nd, void* key, void* value);

    nodeStatus addNode (Node** list, void* key, void* value);

    void destroyNode (Node* nd, elemDestroy func);

    void destroyList (Node* list, elemDestroy func);

    void printList (Node* list, printFunc f);

    void* getKey (Node* list);

    void* getVal (Node* list);

    Node* getNext (Node* list);

    void setVal (Node* nd, void* value );

    void setNext (Node* father, Node* son);

#endif