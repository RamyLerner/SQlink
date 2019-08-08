#include<stdio.h>
#include<string.h>

int myStrcmp(const char* s1, const char* s2){
	int i=0, res=0;
	
	while (s1[i]!='\0' || s2[i]!='\0'){
		if (s1[i]!=s2[i]){
			res = s1[i] - s2[i];
			break;
		}
		i++;	
	}
	return res;
}

char* myStrcpy(char* s1, const char* s2)
{
	int i=0;
	while (s2[i]!='\0'){
		s1[i] = s2[i];
		i++;
	}
	s1[i] ='\0';
}

char* myStrcat(char* s1, const char* s2)
{
	int i=0,j=0;
	while (s1[i]!='\0')
		i++;
	while (s2[j]!='\0'){
		s1[i] = s2[j];
		i++;
		j++;
	}
	s1[i] = '\0';
}

int main(){
		
	char str1[10] = "gg";
	char str2[10] = "ramm";
	char* res;
	/*printf("cmp: %d\n",myStrcmp(str1, str2));*/
	/*printf("cpy: %s\n",myStrcpy(str1, str2));*/
	res = myStrcat(str1, str2);
	printf("cat: %s\n",res);

}
