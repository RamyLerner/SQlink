#include<stdlib.h>
#include<stdio.h>
#include"dynamic.h"

DA_t* createDA(int capacity){
	DA_t* da = (DA_t*)malloc(sizeof(DA_t));
	if (da == NULL)
		return NULL;
	da->cap = capacity;
	da->index = 0;
	da->arr = (intPtr*)malloc(capacity * sizeof(intPtr));
	if (da->arr == NULL){
		free(da);
		return NULL;	
	}
	return da;
}

int insert(DA_t* da, intPtr numPtr){
	intPtr* temp;
	if (da == NULL || da->arr == NULL || numPtr == NULL)
		return 0;
	if(da->index == da->cap){
		temp = da->arr;		
		da->arr = (intPtr*)realloc(da->arr, da->cap * 2 * sizeof(intPtr));
		if (da->arr == NULL){
			free(temp);
			return 0;
		}
		da->cap *=2;
		printf("more space has been allocated\n");
	}
	da->arr[da->index] = numPtr;
	da->index++;
	return 1;
}

void printDA(DA_t* da){
	int i;	
	if (da == NULL || da->arr == NULL){
		printf("print failed, NULL pointer");
		return;
	}
	printf("array so far: ");
	for (i=0; i<da->index; i++)
		if(da->arr[i] != NULL)		
			printf("%d ",*(da->arr[i]));
	putchar('\n');
}

void destroyDA(DA_t* da){
	int i;
	if (da != NULL){
		if (da->arr != NULL){
			for (i=0; i<da->index; i++)
				free(da->arr[i]);
			free(da->arr);
		}
		free(da);
	}
}
