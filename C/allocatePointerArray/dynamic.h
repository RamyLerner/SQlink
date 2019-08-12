#ifndef DYNAMIC_H
#define DYNAMIC_H
	typedef int* intPtr;	
	struct DA{
		int cap;
		int index;
		intPtr* arr;
	};
	typedef struct DA DA_t;
	
	DA_t* createDA(int cap);
	int insert(DA_t* da, intPtr num);
	void printDA(DA_t* da);
	void destroyDA(DA_t* da);
#endif
