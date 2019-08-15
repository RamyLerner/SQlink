#include<stdio.h>
#include<stdlib.h>
#include"myDate.h"

int main(){
	cDate_t *da1 = NULL, *da2 = NULL;
	char name[9];
	int m, y, d, input = 0, format;


	printf("test cDate:\n creating new cDate: enter day, month, year\n");
	scanf("%d%d%d", &d, &m, &y);
	da1 = createDate(d, m, y);
	input = 0;
	while (input != -1){
		printf("type 1 to print\n");
		printf("type 2 to retrieve day\n");
		printf("type 3 to retrieve month\n");
		printf("type 4 to retrieve year\n");
		printf("type 5 to retrieve day of year\n");
		printf("type 6 to check leap\n");
		printf("type 7 to retrieve name of month\n");
		printf("type 8 to set\n");
		printf("type 9 to add\n");
		printf("type -1 to exit\n");
		scanf("%d", &input);
		switch (input){
			case 1: printf("enter format\n");
				scanf("%d", &format);
				printDate(da1, format);
				break;
			case 2: printf("day: %d\n", getDay(da1));
				break;
			case 3: printf("minute: %d\n", getMonth(da1));
				break;
			case 4: printf("second: %d\n", getYear(da1));
				break;
			case 5: printf("%d\n", dayOfYear(da1));
				break; 
			case 6: printf("%d\n", isLeap(da1));
				break;
			case 7: printf("%s\n", monthName(da1, name));
				break;
			case 8: printf("enter new day, month, year\n");
				scanf("%d%d%d", &d, &m, &y);
				setDate(da1, d, m, y);
				printf("done\n");
				break;
			case 9:	printf("creating cDate to add. enter day, month, year\n");
				scanf("%d%d%d", &d, &m, &y);
				da2 = createDate(d, m, y);
				addDates(da1, da2);
				printf("done\n");
				break;
		}
	}

	free(da1);
	free(da2);

}
