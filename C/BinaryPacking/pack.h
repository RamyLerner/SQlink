#ifndef PACK_H
#define PACK_H

int compress(char* s);
int compress2(char* s);

struct pairS{
	unsigned int right :4;
	unsigned int left:4;
};
typedef struct pairS pairS_t;



union pairU{
	pairS_t pair;
	char c;
};

#endif
