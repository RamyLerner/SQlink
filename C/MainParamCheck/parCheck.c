#include<string.h>
#include<stdio.h>

int isInt(char* s){
	int i;	
	for(i=0; i<strlen(s); i++)
		if (!isdigit(s[i]))
			return 0;
	return 1;
}

int isName(char* s){
	int i;	
	for(i=0; i<strlen(s); i++)
		if (!isalpha(s[i]))
			return 0;
	return 1;
}

int main(int argc, char* argv[]){
	char *name, *age;
	int flag = 0;
		
	if (argc != 3){
		printf("3 parameters only\n");
		return;
	}
	if (isInt(argv[1])){
		if (isName(argv[2])){
			age = argv[1];
			name = argv[2];
			flag = 1;
		}
	}
	if (isInt(argv[2])){
		if (isName(argv[1])){
			age = argv[2];
			name = argv[1];
			flag = 1;
		}
	}
	if (flag)
		printf("%s %s\n",name ,age);
	else
		printf("wrong output\n");
}
