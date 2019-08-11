#include<stdio.h>
#include"dynamic.h"

int main(){
	DA_t* da;
	int capacity, num, result;
	
	printf("enter the initial capacity\n");
	do{
		scanf("%d",&capacity);
		if (capacity < 0)
			printf("capacity cannot be negative. please try again\n");
	}while (capacity<0);
	da = createDA(capacity);
	while (1){
		printf("eneter a number to insert, or -1 to print\n");
		scanf("%d",&num);
		if (num == -1) break;
		result = insert(da, num);
		if (!result){
			printf("insertion failed\n");
			break;
		}
	}
	printDA(da);
	destroyDA(da);
}
