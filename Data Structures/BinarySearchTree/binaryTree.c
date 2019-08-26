#include <stdlib.h>
#include <stdio.h>
#include "binaryTree.h"

struct tNode{
	int elem;
	struct tNode* left;
	struct tNode* right;
};

typedef struct tNode tNode;

struct binaryTree{
	tNode* root;
};


bTree* createTree(){
	bTree* bt;
	bt = (bTree*)malloc(sizeof(bTree));
	if (bt)
		bt->root = NULL ;
	return bt;
}


int isEmpty(bTree* bt){
	if (bt == NULL)
		return 0;
	return (bt->root == NULL);
}



static tNode* createNode(int elem){
	tNode* nd;
	nd = (tNode*)malloc(sizeof(tNode));
	if (nd){
		nd->elem = elem;
		nd->left = NULL;
		nd->right = NULL;
	}
	return nd;
}

btStatus insertTree(bTree* bt, int n){
	tNode *nd, *scan, *father;
	if (bt == NULL)
		return NullPointerError;
	nd = createNode(n);
	if (nd == NULL)
		return AllocationError;
	if (isEmpty(bt)){
		bt->root = nd;
		return OK;
	}
	scan = bt->root;
	while (scan != NULL){
		father = scan;
		if (n > scan->elem)
			scan = scan->right;
		else
			scan = scan->left;
	}
	if (n > father->elem)
		father->right = nd;
	else
		father->left = nd;
	return OK;	
}


int searchTree(bTree* bt, int n){
	tNode* scan;
	if (bt == NULL || isEmpty(bt))
		return 0;
	scan = bt->root;
	while (scan != NULL){
		if (scan->elem == n)
			return 1;
		if (n > scan->elem)
			scan = scan->right;
		else
			scan = scan->left;
	}
	return 0;
}

/****************************DELETE FUNCTIONS*/

static isLeaf(tNode* nd){
	return (nd != NULL && nd->left == NULL && nd->right == NULL);
}

static tNode* findNode(bTree* bt, int n){
	tNode* nd;
	if (bt == NULL)
		return NULL;
	nd = bt->root;
	while (nd != NULL){
		if (nd->elem == n)
			return nd;
		if (n > nd->elem)
			nd = nd->right;
		else
			nd = nd->left;
	}
	return NULL;
}

btStatus deleteTree(bTree* bt, int elem){
	btStatus res
	tNode *nd, *child, *temp;
	if (bt == NULL || bt->root == NULL)
		return NullPointerError;
	nd = findNode(bt, elem);
	if (nd == NULL)
		return ElementNotFound;
	if (isLeaf(nd)){
		nd = NULL;
	}
	else{
		if (nd->right == NULL)
			child = nd->left;
		if (nd->left == NULL)
			child = nd->right;
		temp = nd;d
		
		
	}
	
}



static btStatus destroyNode(tNode* nd){
	if (nd == NULL)
		return NullPointerError;
	destroyNode(nd->left);
	destroyNode(nd->right);
	free(nd);
	return OK;
}

btStatus destroyTree(bTree* bt){
	btStatus res;
	if (bt == NULL)
		return NullPointerError;
	res = destroyNode(bt->root);
	free (bt);
	return res;
}


static void printNode(tNode* nd){
	if (nd == NULL)
		return;
	printNode(nd->left);
	printf("%d ", nd->elem);
	printNode(nd->right);
}

void printTree(bTree* bt){
	if (bt != NULL)
		printNode(bt->root);
}
