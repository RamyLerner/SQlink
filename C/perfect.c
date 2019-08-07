#include<stdio.h>
#include<math.h>

int perfect(int n){
	int i, sum=0;
	for (i=1; i<=sqrt(n); i++){
		if (n%i == 0){
			sum += i;
			if (i != sqrt(n))
				sum += (n/i);
		}
	}
	return (sum == n*2)?1:0;	
	
}

int main(){
	int n;	
	do{
		printf("enter a positiv number: ");
		scanf("%d",&n);
		if (n<0)
			printf("oops, that's negative!\n");
	} while (n<0);
	printf("\n%d\n",perfect(n));
		
}
