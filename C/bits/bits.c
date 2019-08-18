#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bits.h"

static const intSize = sizeof(int)*8;

Bitmap_t* createBitmap (int nf){
	int capacity;
	unsigned int *arr;
	Bitmap_t* bm = (Bitmap_t*)malloc(sizeof(Bitmap_t*));
	if (bm == NULL)
		return NULL;
	
	capacity = nf/intSize + 1;
	arr = (unsigned int*)calloc(capacity, sizeof(int));
	if (arr == NULL)
		return NULL;
	bm->nf = nf;
	bm->arr = arr;
	return bm;
}


static  char* int2bin(unsigned int num, char* bin, int size){
	int i=0;
	/*build binary string*/
	for (i=size-1; i>=0; i--){
		bin[i] = num%2 + '0';

		num/=2;
	}
	return bin;
}


	
int printBitmap (Bitmap_t* bm){
	int i, j, capacity;
	char* bin;
	if (bm == NULL)
		return 0;
	bin = (char*) malloc(sizeof(char*) * intSize);
	if (bin == NULL)
		return 0;
	capacity = bm->nf/intSize + 1;	
	for (i=0; i<capacity -1; i++){
		int2bin(bm->arr[i], bin, intSize);
		for (j=0; j<intSize; j++)
			putchar(bin[j]);
	}
	int2bin(bm->arr[capacity -1], bin, intSize);
	for (j=0; j < bm->nf % intSize; j++)
		putchar(bin[j]);
	putchar('\n');
	free (bin);
	return 1;
}


static int setTemp (Bitmap_t* bm, int bit){
	int temp = 1;
	if((bm->nf - bit - 1) >=  (bm->nf / intSize * intSize)){ /*if last*/
		temp <<= (intSize - (bm->nf % intSize));
	}
	else{
		bit = bm->nf - bit -1; /*real bit index*/	
		bit %= intSize; /* realindex of bit in element*/
		bit = intSize - bit - 1; /*binary index of bit in element*/
	}
	temp <<= bit;
	return temp;
}


static int findIntIndex(Bitmap_t* bm, int bit){
	bit = bm->nf - bit -1; /*real bit index*/	
	return bit / intSize;
}


static int bitfuncInputCheck(Bitmap_t* bm, int bit){
	if (bm == NULL)
		return 1;
	if (bit >= bm->nf)
		return 2;
	return 0;
}


int bitOn (Bitmap_t* bm, int bit){
	int intIndex, temp = 1, check;
	
	check = bitfuncInputCheck(bm, bit); 
	if (check != 0)
		return check;
	temp = setTemp(bm, bit);
	intIndex = findIntIndex(bm, bit);
	bm->arr[intIndex] |= temp;	
	return 0;	
}




int bitOff (Bitmap_t* bm, int bit){
	int intIndex, temp = 1, check;
	
	check = bitfuncInputCheck(bm, bit); 
	if (check != 0)
		return check;
	temp = setTemp(bm, bit);
	intIndex = findIntIndex(bm, bit);
	temp = ~temp;
	bm->arr[intIndex] &= temp;	
	return 0;
}



int bitStatus (Bitmap_t* bm, int bit){
	int intIndex, temp = 1, check;
	
	check = bitfuncInputCheck(bm, bit); 
	if (check != 0)
		return check;
	temp = setTemp(bm, bit);
	intIndex = findIntIndex(bm, bit);
	return (bm->arr[intIndex] & temp) ? 3 : 0;	
}


void destroyBitmap (Bitmap_t* bm){
	if (bmm != NULL)
		free(bm->arr);
	free(bm);
}


int useBitfunc (bitfunc bf, Bitmap_t* bm, int n){
	int check = bitfuncInputCheck(bm, n); 
	if (check != 0)
		return check;
	return bf(bm, n);
}
