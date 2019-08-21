#include<stdio.h>
#include"darray_int.h"

struct darray{
	int* arr;
	size_t initialCap;
	size_t capacity;
	size_t size;
};


AdtStatus darrayCreate(darray **dArr, size_t initial_capacity){
	int* arr;

	*dArr = (darray*)malloc(sizeof(darray));
	if (dArr == NULL)
		return AllocationError;
	arr = (int*)malloc(sizeof(int) * initial_capacity);
	if (arr == NULL){
		free(*dArr);
		return AllocationError;
	}
	(*dArr)->arr = arr;
	(*dArr)->initialCap = initial_capacity;
	(*dArr)->capacity = initial_capacity; 
	(*dArr)->size = 0;
	return OK;
}


AdtStatus darrayDestroy(darray *dArr){
	if (dArr != NULL)
		free(dArr -> arr);
	free (dArr);
	return OK;
}


AdtStatus   darrayAdd(darray *dArr,  int  _item){
	int* temp;
	if (dArr == NULL)
		return NullPointerError;
	if (dArr->size == dArr->capacity){
		temp = dArr->arr;
		dArr->arr = (int*)realloc(dArr->arr, dArr->capacity * 2 * sizeof(int));
		if (dArr->arr == NULL){
			dArr->arr = temp;
			return AllocationError;
		}
		dArr->capacity *= 2;
		printf("reallocated\n");
	}
	dArr->arr[dArr->size] = _item; 
	dArr->size++;
	return OK;
}


AdtStatus   darrayDelete(darray *dArr,  int* _item){
	int* temp;
	*_item = dArr->arr[dArr->size - 1];
	if (dArr == NULL)
		return NullPointerError;
	if (dArr->capacity > dArr->initialCap && dArr->size <= dArr->capacity * 3 / 8){
		temp = dArr->arr;
		dArr->arr = (int*)realloc(dArr->arr, dArr->capacity / 2 * sizeof(int));
		if (dArr->arr == NULL){
			dArr->arr = temp;
			return AllocationError;
		}
		dArr->capacity /= 2;
		printf("reallocated\n");
	}
	dArr->size--;
	return OK;
}


AdtStatus   darrayGet(darray *dArr, size_t _index, int *_item){
	if (dArr == NULL)
		return NullPointerError;
	if (_index >= dArr->size)
		return IndexError;
	*_item = dArr->arr[_index];
	return OK;
}


AdtStatus   darraySet(darray *dArr, size_t _index, int  _item){
	if (dArr == NULL)
		return NullPointerError;
	if (_index >= dArr->size)
		return IndexError;
	dArr->arr[_index] = _item;
	return OK;
}


AdtStatus   darrayItemsNum(darray *dArr, int *_numOfItems){
	if (dArr == NULL)
		return NullPointerError;
	*_numOfItems = dArr->size;
	return OK;
}


AdtStatus darrayPrint(darray *dArr){
	int i;
	if (dArr == NULL)
		return NullPointerError;
	for (i=0; i<dArr->size; i++)
		printf("%d ",dArr->arr[i]);
	putchar('\n');
	return OK;
}