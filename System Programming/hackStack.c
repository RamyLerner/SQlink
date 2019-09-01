#include<stdio.h>

typedef void(*func)(int);

void b(int n){
	printf("Inside B\n");
}

int a(int n1){
	func f = b;
	
	printf("Inside A\n");
	*(&n1 - 1) = (int)f;
	return 7;
}

int main(){
	int res;
	printf("Inside main\n");
	res = a(6);
}