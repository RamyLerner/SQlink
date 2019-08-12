#include<stdio.h>
#include<stdlib.h>
#include"dynamic.h"

int main(){
	DA_t* da;
	int capacity, result;
	intPtr numPtr;
	
	printf("enter the initial capacity\n");
	do{
		scanf("%d",&capacity);
		if (capacity < 0)
			printf("capacity cannot be negative. please try again\n");
	}while (capacity<0);
	da = createDA(capacity);
	while (1){
		printf("eneter a number to insert, or -1 to print\n");
		
		numPtr = (intPtr)malloc(sizeof(int));
		scanf("%d",numPtr);
		if(numPtr == NULL)
			break;
		if (*numPtr == -1) break;
		result = insert(da, numPtr);
		if (!result){
			printf("insertion failed\n");
			break;
		}
	}
	printDA(da);
	destroyDA(da);
}
