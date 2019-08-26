#ifndef BST_H
#define BST_H

	typedef struct binaryTree bTree;
	
	typedef enum {INORDER, PREORDER, POSTORDER} Sorder;	
	typedef enum {OK, AllocationError, NullPointerError, ElementNotFound} btStatus;
	
	bTree* createTree();
	
	btStatus insertTree(bTree* bt, int elem);
	
	int searchTree(bTree* bt, int elem);
	
	btStatus deleteTree(bTree* bt, int elem);
	
	btStatus destroyTree(bTree* bt);
	
	/*void walk(elemFunc func, Sorder o);*/
	
	int isEmpty(bTree* bt);
	

#endif