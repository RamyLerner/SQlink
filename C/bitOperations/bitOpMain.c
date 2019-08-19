#include<stdio.h>
#include "bitOp.h"

int main(){
	unsigned char num, y;
	unsigned int numInt, numInt2;
	int input, rot, i, j, value, n, p;
	int* err;
	
	*err = 0;
	while (input != -1){
		printf("type 1 for invert()\ntype 2 for rotate()\ntype 3 for setBits1()\ntype 4 for setBits2()\ntype -1 to exit\n");
		scanf("%d", &input);
		switch (input){
			case 1: do{
					printf("enter a 1 byte number\n");
					scanf("%u",&numInt);
				} while (numInt > 255);
				num = (char)numInt;
				printf("x = ");
				char2bin(num);
				printf("x inverted = ");
				char2bin(invert(num));
				break;
			case 2: do{
					printf("enter a 1 byte number\n");
					scanf("%u",&numInt);
				} while (numInt > 255);
				num = (char)numInt;
				printf("enter # of rotate\n");
				scanf("%d",&rot);
				printf("x = ");
				char2bin(num);
				printf("x rotated by %d = ", rot);
				char2bin(rotate(num, rot));
				break;
			case 3: do{
					printf("enter a 1 byte number\n");
					scanf("%u",&numInt);
				} while (numInt > 255);
				num = (char)numInt;
				printf("enter n, p, y\n");
				scanf("%d%d%u", &n, &p, &numInt2);
				y = (char)numInt2;
				printf("x = ");
				char2bin(num);
				printf("y = ");
				char2bin(y);
				printf("setBits n=%d, p=%d gives x=", n, p);
				char2bin(setBits1(num, p, n, value, err));
				if (*err != 1)
					printf("invalid input\n");
				break;
			case 4: printf("enter a 4 byte integer\n");
				scanf("%u",&numInt);
				printf("enter i, j, value\n");
				scanf("%d%d%d", &i, &j, &value);
				printf("x = ");
				int2bin(numInt);
				printf("setBits i=%d, j=%d, value=%d gives x=", i, j, value);
				int2bin(setBits2(numInt, i, j, value, err));
				if (*err == 1)
					printf("invalid input\n");
				break;
			case -1: break;
			default: printf("invalid input\n");
				
		}
	}
}
