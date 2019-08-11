#include<stdio.h>
#include<string.h>

void int2bin(){
	int num, i=0, j;
	char bin[33];
	
	/*input + input check*/
	printf("enter a positiv decimal integer:\n");
	do{
		scanf("%d",&num);	
		if (num<0){
			printf("not positiv, try again\n");
		}
	}while (num<0);

	/*build binary string*/
	do{
		bin[i] = num%2 + '0';
		num/=2;
		i++;
	}while (num!=0);
	bin[i] = '\0';

	/*print binary string*/
	printf("binary representation:\n");
	for (j=i-1; j>=0; j--)
		putchar(bin[j]);
	putchar('\n');
}
	

void bin2int(){
	char bin[33];
	int i, sum=0, flag,len;	

	/*input + input check*/	
	printf("enter a positiv binary integer:\n");
	do{
		scanf("%s",bin);
		len = strlen(bin);
		flag=0;
		for (i=0; i<len && flag==0; i++)
			if (bin[i]!='0' && bin[i]!='1'){ /*input check*/
				flag=1;
				printf("not a positiv binary number, try again\n");
			}
	}while (flag==1);

	/*calculate result*/
	for (i=0; i<len; i++) 
		sum = sum*2+(bin[i]-'0'); 

	/*print result*/
	printf("decimal: %d\n",(int)sum);
}

char* squeeze(char *s1, const char *s2){
	int i,j,k;
	if (s1==NULL || s2==NULL)
		return s1;
	for (i=0; s1[i]!='\0'; i++) /*go over squeezable string*/
		for (j=0; j<strlen(s2); j++) /*go over char pool to delet*/
			if (s1[i] == s2[j]){
				for (k=i; s1[k]!='\0'; k++) /*delete letter*/
					s1[k] = s1[k+1];
				i--;	
			}
	return s1;
					

}

int location(char *s1, char *s2){
	int len1, len2, i=0, j, flag=0, last;

	/*input check*/
	if (s1==NULL || s2==NULL)
		return -1;
	len1 = strlen(s1);
	len2 = strlen(s2);
	
	while (i<=len1-len2){ /*look for a starting point*/
		if (s1[i]==s2[0]){ /*found a potential match*/
			flag = 1;
			for (j=1; flag==1 && j<len2; j++){
				if (s1[j+i] != s2[j]){
					flag = 0;
				}
				last = i+j;
			}
			if (flag)
				return i;
			i = last;
		}
		i++;
	}
	return -1;

}

int main(){
	int input, result;	
	char s1[40], s2[40];
	while(1){	
		printf("type 1 for int2bin()\ntype 2 for bin2int()\ntype 3 for squeeze()\ntype 4 for location()\nenter a negative integer to exit\n");
		scanf("%d",&input);
		if (input < 0) break;
		switch (input){
			case 1: int2bin();
				break;
			case 2: bin2int();
				break;
			case 3: printf("enter a string:\n");
				scanf("%s",s1);
				printf("enter character to delete:\n");
				scanf("%s",s2);
				printf("squeezed string: %s\n", squeeze(s1,s2));
				break;
			case 4: printf("enter two strings:\n");
				scanf("%s",s1);
				scanf("%s",s2);
				printf("result: %d\n", location(s1,s2));
				break;
			default: printf("please try again\n");
		}
	}
}
		
