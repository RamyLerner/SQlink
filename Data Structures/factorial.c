#include<stdio.h>

unsigned int factorial (unsigned int n){
	if (n == 1)
		return n;
	return n * factorial(n-1);
}

int main(){
	unsigned int n;
	printf("input: ");	
	scanf("%u", &n);
	printf("factorial: %u\n", factorial(n));
}
