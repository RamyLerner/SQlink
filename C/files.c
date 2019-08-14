#include<stdlib.h>
#include<stdio.h>

int letterFreq(char* fileName){
	FILE* fp;
	char c;
	int i, upper[26]={0}, lower[26]={0};
	if(!(fp = fopen(fileName,"r")))
		return 0;
	while((c=fgetc(fp)) != EOF){
		if (islower(c))
			lower[c -'a']++;
		if (isupper(c))
			upper[c - 'A']++;
	}
	for (i=0; i<26; i++)
		if (lower[i] != 0)
			printf("%c: %d\n", i+'a', lower[i]);
	for (i=0; i<26; i++)
		if (upper[i] != 0)
			printf("%c: %d\n", i+'A', upper[i]);
	return 1;
	
			
}

int wordFreq(*char fileName){
	FILE* fp;

	if(!fp=fopen(fileName,"r"))
		return 0;
	while((
