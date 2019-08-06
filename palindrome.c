#include<stdio.h>

int palindrome(int n){
	int newN=0, m=n;
	while (m!=0){
		newN *= 10;		
		newN += m%10;
		m/=10;
	}
	if (n == newN)
		return 1;
	else
		return 0;
}

int main(){
	int n;	
	do{
		printf("enter a positiv number: ");
		scanf("%d",&n);
		if (n<0)
			printf("oops, that's negative!\n");
	} while(n<0);
	printf("\n%d\n",palindrome(n));
		
}

