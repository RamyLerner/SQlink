#include<stdio.h>
#include"diary.h"

int main(){
	Calendar_t* c;
	Meeting_t* m;
	int input, room, res, capacity;
	float start, finish;
	
	printf("enter capacity\n");
	scanf("%d",&capacity);	
	c = createAD(capacity);
	if (!loadFromFile(c)){
		perror("loading from file failed\n");		
		return -1;
	}
	do{
		printf("type 1 to insert\ntype 2 to print\ntype 3 to find\ntype 4 to remove\ntype -1 to exit\n");
		scanf("%d",&input);
		switch (input){
			case 1: printf("enter start and finish times and room number: \n");
				scanf("%f%f%d", &start, &finish, &room);
				m = createMeeting(start, finish, room);
				res = insertMeeting(c, m);
				if (!res)
					printf("insert failed\n");
				break;
			case 2: printAD(c);
				break;
			case 3: printf("enter starting hour\n");
				scanf("%f",&start);
				m = findMeeting(c, start);
				if (m == NULL)
					printf("meeting was not found\n");
				else
					printf("meeting from %f until %f in room no. %d\n", m->begin, m->end, m->room);	
				break;
			case 4: printf("enter starting hour\n");
				scanf("%f",&start);
				removeMeeting(c, start);
				printf("done\n");
		}
	}while (input != -1);

	/*on exit*/
	if (!saveInFile(c)){
		perror("saving on file failed\n");
		return -1;
	}
	destroyAD(c);
}
