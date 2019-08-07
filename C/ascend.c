#include<stdio.h>

int ascending(int n){
	int max = n%10;
	while (n!=0){
		if (n%10 > max)
			return 0;
		max = n%10;
		n /= 10;
	}
	return 1;
}


int main(){
	int n;	
	do{
		printf("enter a positiv number: ");
		scanf("%d",&n);
		if (n<0)
			printf("oops, that's negative!\n");
	} while(n<0);
	printf("\n%d\n",ascending(n));
		
}
