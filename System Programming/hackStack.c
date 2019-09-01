#include<stdio.h>

void b(int n){
	printf("Inside B\n");
}

int a(int n1){
	printf("Inside A\n");
	*(&n1 - 1) = (int)b;
	return 7;
}

int main(){
	int res;
	printf("Inside main\n");
	res = a(6);
	return 0;
}