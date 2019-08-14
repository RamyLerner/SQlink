#include<stdio.h>

int main(){
	int input = 0;
	char fName[1024];
	while (input != -1){	
		printf("type 1 for lastNLines()\ntype 2 for letterFreq()\ntype 3 for wordFreq()\ntype -1 to exit\n");
		scanf("%d",&input);
		switch(input){
			case 2: printf("enter file name\n");
				scanf("%s", fName);
				if (letterFreq(fName)==0)
					printf("letterFreq failed\n");
				break;
		}
	}
}
