#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include "destroyFunc.h"
#define N 5

struct Node{
	void* key;
	void* value;
	struct Node* next;
};



nodeStatus createNode(Node** nd, void* key, void* value){
	*nd = (Node*)malloc(sizeof(Node));
	if (*nd == NULL)
		return nAllocationError;
	(*nd)->key = key;
    (*nd)->value = value;
	(*nd)->next = NULL;
	return nOK;
}

Node* createList(){
	return NULL;
}


nodeStatus addNode (Node** list, void* key, void* value){
	Node* nd, first;
    nodeStatus res;
    
    if (list == NULL)
        return nNullPointerError;

    res = createNode(&nd, key, value);

    if (res == nOK){
        nd->next = *list;
        *list = nd;
    }
    return res;
}


void printList (Node* list, printFunc f){
	while (list != NULL){
		f(list->key, list->value);
		list = list->next;
	}
	printf("NULL\n");
}


void destroyNode (Node* nd, elemDestroy func){
    func(nd->key, nd->value);
	free(nd);
}

void destroyList (Node* list, elemDestroy func){
	Node* nextNd;
	while(list != NULL){
		nextNd = list->next;

		destroyNode (list, func);
		list = nextNd;
	}
}

void* getKey (Node* nd){
    return nd->key;
}

void* getVal (Node* nd){
    return nd->value;
}

Node* getNext (Node* nd){
    return nd->next;
}

void setVal (Node* nd, void* value ){
    nd->value = value;
}

void setNext (Node* father, Node* son){
    father->next = son;
}

void listCat (Node** l1, Node* l2){
	Node* temp = *l1;
	if (*l1 == NULL){
		*l1 = l2;
		return;
	}
	if (l2 == NULL) return;
	while (temp->next != NULL) 
		temp = temp->next;
	
	temp->next = l2;
}

int listSize (Node* list){
	int size = 0;
	while (list != NULL){
		size++;
		list = list->next;
	}
	return size;
}