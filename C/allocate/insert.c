#include<stdio.h>
#include<stdlib.h>



int* insert(int num, int* ip, int* index, int* cap){
	int* temp;
	int i;
	if (index==NULL || cap==NULL || index==NULL){
		printf("NULL pointer\n");
		return NULL;
	}
	if (*index == *cap){
		temp = ip;
		ip = (int*)realloc(ip, sizeof(int) * (*cap+1));
		if (ip == NULL){
			printf("allocation failed\n");
			return temp;
		}
		*cap = *cap + 1;
		printf("another place allocated\n");
	}		
	ip[*index] = num;
	
	printf("array so far: ");
	for (i=0; i<=*index; i++)
		printf("%d ",ip[i]);
	putchar('\n');

	*index = *index + 1;
	return ip;	
}

int main(){
	int num, index=0, cap;
	int* ip;
	printf("enter initial capacity\n");
	do{
		scanf("%d",&cap);
		if (cap<0)
			printf("invalid input, try again\n");
	}while (cap<0);
	ip = (int*)malloc(cap * sizeof(int));
	while(1){	
		printf("enter a number or -1 to exit\n");
		scanf("%d",&num);
		if (num == -1) break;	
		ip = insert(num, ip, &index, &cap);
		if (ip == NULL) break;
	}
	free(ip);
}
