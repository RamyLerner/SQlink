#include <stdio.h>
#include <string.h>
#include "pack.h"

int compress(char* s){
	char new=0;
	int orI, compI=0, size = strlen(s);
	for (orI=0; orI<size; orI+=2){	
		new = s[orI] - 'a';
		new <<= 4;
		if (orI<size-1)
			new |= (s[orI+1] - 'a');
		s[compI] = new;
		compI++;
	}	
	
	for (orI=compI; orI<size; orI++)
		s[orI] = 0;
	
	return size;
}


int compress2(char* s){
	char new=0;
	union pairU p;
	int orI, compI=0, size = strlen(s);
	for (orI=0; orI<size; orI+=2){	
		p.pair.left = s[orI] - 'a';
		if (orI<size-1)
			p.pair.right = s[orI] - 'a';
		s[compI] = p.c;
		compI++;
	}	
	
	for (orI=compI; orI<size; orI++)
		s[orI] = 0;
	
	return size;
}


void char2bin(char num){
	int i=0, j;
	char bin[8];
	int size = 8;
	
	for (i=size-1; i>=0; i--){
		bin[i] = num%2 + '0';

		num/=2;
	}
	for (j=0; j < size; j++)
		putchar(bin[j]);
	putchar(' ');

}
