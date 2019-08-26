#include <stdio.h>
#include <stdlib.h>
#include "binaryTree.h"

int main(){
	bTree* bt;
	int input = 0, elem;
	bt = createTree();
	while (input != -1){
		printf("1 to insert\n2 to search\n3 to print\n-1 to exit\n");
		scanf("%d", &input);
		switch (input){
			case 1: printf("enter new element\n");
				scanf("%d", &elem);
				if (insertTree(bt, elem)== OK)
					printf("OK\n");
				else
					printf("oops\n");
				break;
			case 2: printf("enter element to search\n");
				scanf("%d", &elem);
				printf("%d\n", searchTree(bt, elem));
				break;
			case 3: printTree(bt);
				putchar('\n');
				break;
			case -1: break;
		};
	}
	destroyTree(bt);
}