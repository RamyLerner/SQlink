#include <stdio.h>
#include "bitOp.h"


void char2bin(unsigned char num){
	int i=0, j;
	char bin[8];
	int size = 8;
	
	for (i=size-1; i>=0; i--){
		bin[i] = num%2 + '0';
		num/=2;
	}
	for (j=0; j < size; j++)
		putchar(bin[j]);
	putchar('\n');
}

void int2bin(unsigned int num){
	int i=0, j;
	char bin[32];
	int size = 32;
	
	for (i=size-1; i>=0; i--){
		bin[i] = num%2 + '0';
		num/=2;
	}
	for (j=0; j < size; j++)
		putchar(bin[j]);
	putchar('\n');
}
	

unsigned char invert(unsigned char n){
	return n ^ ~0;
}

unsigned char rotate(unsigned char n, int times){
	int i;	
	for (i=0; i<times; i++)
		if (n & 128)/*msb == 1*/
			n = (n<<1) | 1;
		else n = n<<1;
	return n;
}


unsigned char setBits1(unsigned char x, int p, int n, unsigned char y, int* err){
	int k;	
	unsigned char aligned, temp=0;
	if (p<0 || p>31 ||n<1 || n>p+1){
		*err = 1;
		return 0;
	}
	for (k=0; k<n; k++)
		temp = (temp<<1) | 1;
	aligned = temp << (p-n+1);
	return (y & temp)<<(p-n+1) | (x & ~aligned);
}


unsigned int setBits2(unsigned int x, int i, int j, int value, int* err){
	int k;	
	unsigned int temp=0;
	if (i<0 || i>31 ||j<i || j>31){
		*err = 1;
		return 0;
	}
	for (k=0; k<j-i+1; k++)
		temp = (temp<<1) | 1;
	temp <<= i;
	return value ? x|temp : x&(~temp);
}
