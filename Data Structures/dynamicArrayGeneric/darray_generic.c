#include<stdio.h>
#include"darray_generic.h"

struct darray{
	void** arr;
	size_t initialCap;
	size_t capacity;
	size_t size;
};


AdtStatus darrayCreate(darray **dArr, size_t initial_capacity){
	void** arr;

	*dArr = (darray*)malloc(sizeof(darray));
	if (dArr == NULL)
		return AllocationError;
	arr = (void**)malloc(sizeof(void*) * initial_capacity);
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


AdtStatus darrayDestroy(darray *dArr, elementDestroy destFunc, void* context){
	int i=0;
    if (dArr != NULL){
        if (dArr->arr != NULL){
            for (i=0; i < dArr->size; i++)
                destFunc(dArr->arr[i], context);
		    free(dArr -> arr);
        }
    }
	free (dArr);
	return OK;
}


AdtStatus   darrayAdd(darray *dArr,  void*  _item){
	void** temp;
	if (dArr == NULL)
		return NullPointerError;
	if (dArr->size == dArr->capacity){
		temp = dArr->arr;
		dArr->arr = (void**)realloc(dArr->arr, dArr->capacity * 2 * sizeof(void*));
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


AdtStatus   darrayDelete(darray *dArr,  void** _item){
	void** temp;
	*_item = dArr->arr[dArr->size - 1];
	if (dArr == NULL)
		return NullPointerError;
	if (dArr->capacity > dArr->initialCap && dArr->size <= dArr->capacity * 3 / 8){
		temp = dArr->arr;
		dArr->arr = (void**)realloc(dArr->arr, dArr->capacity / 2 * sizeof(void*));
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


AdtStatus   darrayGet(darray *dArr, size_t _index, void **_item){
	if (dArr == NULL)
		return NullPointerError;
	if (_index >= dArr->size || _index < 0)
		return IndexError;
	*_item = dArr->arr[_index];
	return OK;
}


AdtStatus   darraySet(darray *dArr, size_t _index, void*  _item){
	if (dArr == NULL)
		return NullPointerError;
	if (_index >= dArr->size || _index < 0)
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


static void swap (void** pt1, void** pt2){
	void* temp = *pt1;
	*pt1 = *pt2;
	*pt2 = temp;
}

static int partition (darray *dArr, int low, int high, elementCompare compFunc)
{
    void* pivot;
	void** arr = dArr->arr;
	pivot = arr[low + (high - low) / 2];
    while(1){
        while (compFunc(arr[low], pivot) > 0)       
            low++;

        while (compFunc(arr[high], pivot) < 0)
            high--;
			 
        if (low >= high)
            return high;

        swap (&arr[low], &arr[high]);

        low++;
        high--;
	}
}

static  void quickSort(darray *dArr, int low, int high, elementCompare compFunc)
{
	int pi;
    if (low < high)
    {
       /*pivot*/
        pi = partition(dArr, low, high, compFunc);

        quickSort(dArr, low, pi - 1, compFunc);  /*Before pi*/
        quickSort(dArr, pi + 1, high, compFunc); /* After pi*/
    }
}

AdtStatus darraySort(darray *dArr, elementCompare compFunc){
	if (dArr == NULL)
		return NullPointerError;
	quickSort(dArr, 0, dArr->size - 1, compFunc);
	return OK;
}