#include <stdio.h>
#include <string.h>
#include "pack.h"

int main(){
	int i, size;	
	char input[22], input2[22];
	
	printf("enter a legal string\n");
	scanf("%s", input);	
	size = strlen(input);
	size = (size%2 ? size/2+1 : size/2);
	strcpy(input2, input);

	compress(input);
	for (i=0; i<size; i++)
		char2bin(input[i]);
	putchar('\n');

	compress2(input2);
	for (i=0; i<size; i++)
		char2bin(input[i]);
	putchar('\n');
}
