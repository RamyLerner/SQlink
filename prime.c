#include<stdio.h>
#include<math.h>

int prime(int n){
	int i;
	double q;
	if (n==1)
		return 0;
	if (n==2)
		return 1;
	q = sqrt(n);	
	for (i=2; i<q+1; i++)
		if (n%i == 0)
			return 0;
	return 1;
}

int main(){
	int n;	
	do{
		printf("enter a positiv number: ");
		scanf("%d",&n);
		if (n<=0)
			printf("oops, that's not positive!\n");
	} while (n<=0);
	printf("\n%d\n",prime(n));
		
}
