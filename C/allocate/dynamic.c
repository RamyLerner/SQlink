#include<stdlib.h>
#include<stdio.h>
#include"dynamic.h"

DA_t* createDA(int capacity){
	DA_t* da = (DA_t*)malloc(sizeof(DA_t));
	if (da == NULL)
		return NULL;
	da->cap = capacity;
	da->index = 0;
	da->arr = (int*)malloc(capacity * sizeof(int));
	return da;
}

int insert(DA_t* da, int num){
	int* temp;
	if (da == NULL)
		return 0;
	if(da->index == da->cap){
		temp = da->arr;		
		da->arr = (int*)realloc(da->arr, da->cap * 2 * sizeof(int));
		if (da->arr == NULL){
			free(temp);
			return 0;
		}
		da->cap *=2;
		printf("more space has been allocated\n");
	}
	da->arr[da->index] = num;
	da->index++;
	return 1;
}

void printDA(DA_t* da){
	int i;	
	int* a;
	if (da == NULL){
		printf("print failed, NULL pointer");
		return;
	}
	a = da->arr;
	printf("array so far: ");
	for (i=0; i<da->index;i++)
		printf("%d ",a[i]);
	putchar('\n');
}

void destroyDA(DA_t* da){
	if (da != NULL){
		if(da->arr != NULL)
			free(da->arr);
		free(da);
	}
}
