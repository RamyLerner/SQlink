#include<stdio.h>
void swap(int* x, int* y){
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void sort(int* arr, int n){
	int i,j;
	for (i=1; i<n; i++){
		for (j=i-1; j>=0; j--){
			if (arr[j]>arr[j+1])
				swap(&arr[j],&arr[j+1]);
			else break;
		}
	}
}

void sort01(int* arr, int n){
	int i, sorted=0;
	for (i=1; i<n; i++){
		if (arr[i]==0){
			swap(&arr[i],&arr[sorted]);
			sorted++;
		}	
	}
}

int sortOE(int* arr, int n){
	int i, sorted=0;
	for (i=1; i<n; i++){
		if (arr[i]%2 == 0){
			swap(&arr[i],&arr[sorted]);
			sorted++;
		}	
	}
	return sorted
}


int main(){
	int i,a[8];	
	printf("Enter array of 8 zores or ones\n");
	for(i=0; i<8; i++)
		scanf("%d",&a[i]);
	sort01(a,8);
	printf("Sorted:\n");
	for(i=0; i<8; i++)
		printf("%d ",a[i]);
}
