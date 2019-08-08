#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void lotto(){
	int count = 0, nums[6],/*temp[50] = {0},*/n,flag = 0,i,j,one,ten;
	char form[5][11];

	srand(time(NULL));/*choose 6 number in random*/
	while (count != 6){
		n = rand()%49 + 1;
		/*if (temp[n] != 1){
			temp[n] = 1;
			nums[count] = n;
			count++;	
		}*/
		for (i=0; i<count; i++){
			if (n == nums[i]){
				flag = 1;
				break;
			}
		}
		if (flag == 0){
			nums[count] = n;
			count++;
		}
	}
	for (i=0; i<6; i++) /*/print the 6 chosen numbers*/
		printf("%d ",nums[i]);

	printf("\n\n");	
	
	form[0][0] = ' '; /*print the forms margins*/
	for (i=1; i<=9; i++)
		form[0][i] = i + '0';
	for (i=1; i<=5; i++)
		form[i][0] = i-1 + '0';
	for (i=1; i<=5; i++)/*initialize the form to '-'*/
		for (j=1; j<=10; j++)
			form[i][j] = '-';
	for (i=0; i<6; i++){ /*fill in the chosen numbers*/
		ten = nums[i]/10;
		one = nums[i]%10;
		if (one == 0){
			one = 10;
			ten -= 1;
		}
		form[ten+1][one] = '+';
	}
	form[5][10] = ' ';

	for (i=0; i<=5; i++){/*print the whole form*/
		for (j=0; j<=10; j++)
			printf("%c ",form[i][j]);
		putchar('\n');
	}
}

int main(){
	lotto();
}
