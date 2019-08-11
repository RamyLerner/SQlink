#ifndef DYNAMIC_H
#define DYNAMIC_H
	struct DA{
		int cap;
		int index;
		int* arr;
	};
	typedef struct DA DA_t;
	
	DA_t* createDA(int cap);
	int insert(DA_t* da, int num);
	void printDA(DA_t* da);
	void destroyDA(DA_t* da);
#endif
