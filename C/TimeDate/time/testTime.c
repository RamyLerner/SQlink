#include<stdio.h>
#include<stdlib.h>
#include"myTime.h"

int main(){
	cTime_t *t1 = NULL, *t2 = NULL;
	int h, m, s, input = 0, format;


	printf("test cTime:\n creating new cTime: enter hour, minute, second\n");
	scanf("%d%d%d", &h, &m, &s);
	t1 = createTime(h, m, s);
	while (input != -1){
		printf("type 1 to print\ntype 2 to retrieve hour\ntype 3 to retrieve minute\ntype 4 to retrieve second\ntype 5 to set\ntype 6 to add\ntype -1 to move on\n");
		scanf("%d", &input);
		switch (input){
			case 1: printf("enter format\n");
				scanf("%d", &format);
				printTime(t1, format);
				break;
			case 2: printf("hour: %d\n", getHour(t1));
				break;
			case 3: printf("minute: %d\n", getMinute(t1));
				break;
			case 4: printf("second: %d\n", getSecond(t1));
				break;
			case 5: printf("enter new hour, minute, second\n");
				scanf("%d%d%d", &h, &m, &s);
				setTime(t1, h, m, s);
				printf("done\n");
				break;
			case 6:	printf("creating cTime to add. enter hour, minute, second\n");
				scanf("%d%d%d", &h, &m, &s);
				t2 = createTime(h, m, s);
				addTimes(t1, t2);
				printf("done\n");
				
		}
	}
	

	free(t1);
	free(t2);
		
}
