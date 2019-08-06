#include <stdio.h>

void func1(int N){
	int i,j;	
	for (i=0; i<N; i++){
		for (j=0; j<i+1; j++)		
			putchar('*');
		putchar('\n');
	}
}

void func2(int N){
	int i,j;	
	for (i=0; i<N; i++){
		for (j=0; j<i+1; j++)		
			putchar('*');
		putchar('\n');
	}
	for (i=N-1; i>0; i--){
		for (j=0; j<i; j++)		
			putchar('*');
		putchar('\n');
	}
}

void func3(int N){
	int i,j;
	for (i=1; i<=N; i++){
		for (j=0; j<N-i; j++)
			putchar(' ');
		for (j=0; j<i*2-1; j++)
			putchar('*');
		putchar('\n');
	}
}

int main(){
	int N;	
	printf("Please enter a number ");
	scanf("%d", &N);
	putchar('\n');
	func1(N);
	putchar('\n');
	func2(N);
	putchar('\n');
	func3(N);
}

	
