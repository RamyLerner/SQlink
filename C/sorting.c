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

int sortEO(int* arr, int n){
	int i=0, countEven=0, oddRangeStart, oddRange=0, temp, chain, j;
	
	while (i<n && arr[i] % 2 == 0){
		countEven++;
		i++;
	}
	while (i<n){
		oddRangeStart = i - oddRange;
		while (i<n && arr[i]%2==1){
			oddRange++;
			i++;
		}
		if (i>=n) break;
		while (i<n && arr[i]%2==0){
			i++;
			countEven++;
		}
		/*start swaping chains*/
		for (chain=0; chain<oddRange; chain++){
			temp = arr[oddRangeStart];
			for (j=oddRangeStart; j<=i-2; j++)
				arr[j] = arr[j+1];
			arr[i-1] = temp;
		}
		
	}
	return countEven;


}


int occure(int* arr, int n){
	int i, count=0, current, max_count=0, max_num;
	sort(arr,n);
	current = arr[0];
	for (i=0; i<n; i++){
		if (arr[i] != current){
			current = arr[i];
			count = 1;
		}
		else{
		count++;
		}
		if (count > max_count){
			max_num = arr[i];
			max_count = count;
		}
	}
	return max_num;
}


int main(){
	int i, a[8], res;	
	printf("Enter array of 8 integers\n");
	for(i=0; i<8; i++)
		scanf("%d",&a[i]);
	res = sortEO(a,8);
	printf("Sorted:\n");
	for(i=0; i<8; i++)
		printf("%d ",a[i]);
	putchar('\n');
	printf("number of evens: %d\n", res);
}
