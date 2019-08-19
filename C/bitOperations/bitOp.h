#ifndef BITOP_H
#define BITOP_H

	unsigned char invert(unsigned char);
	unsigned char rotate(unsigned char n, int times);
	unsigned char setBits1(unsigned char x, int p, int n, unsigned char y, int* err);
	unsigned int setBits2(unsigned int x, int i, int j, int value, int* err);


#endif
