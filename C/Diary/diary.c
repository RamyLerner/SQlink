#include<stdio.h>
#include<stdlib.h>
#include"diary.h"


Calendar_t* createAD(int capacity){
	Calendar_t* calPtr = (Calendar_t*)malloc(sizeof(Calendar_t));
	if (calPtr == NULL)
		return NULL;
	calPtr->day = (Meeting_t**)malloc(capacity * sizeof(Meeting_t*));
	if (calPtr->day == NULL){
		free(calPtr);
		return NULL;
	}
	calPtr->capacity = capacity;
	calPtr->amount = 0;
	return calPtr;
}


Meeting_t* createMeeting(float begin, float end, int room){
	Meeting_t* meetPtr;
	if (!(begin<end) || (begin<0) || (begin >=24)  || (end<0) || (end >=24)){
		printf("invalid begin or end time");
		return NULL;
	}
	meetPtr = (Meeting_t*)malloc(sizeof(Meeting_t));
	if (meetPtr == NULL)
		return NULL;
	meetPtr->begin = begin;
	meetPtr->end = end;
	meetPtr->room = room;
	return meetPtr;
}


int insertMeeting(Calendar_t* c, Meeting_t* m){	
	Meeting_t** temp;
	int i=0, insert_index;

	if (c==NULL || m==NULL)
		return 0;

	/*day is empty*/		
	if (c->amount == 0)
		c->day[0] = m;
	else{
		/*expand if neccesary*/		
		if (c->amount == c->capacity){
			temp = c->day;			
						
			c->day = (Meeting_t**)realloc(c->day, c->capacity * 2 * sizeof(Meeting_t*));	
			if (c->day == NULL){
				c->day = temp;
				free(m);
				return 0;

			}
			printf("additional memory allocated\n");			
			c->capacity *= 2;
		}	
		
		while(i < c->amount && c->day[i]->end <= m->begin)
			i++;
		if (c->amount==i || c->day[i]->begin >= m->end)
			insert_index = i;
		else
			return 0;
		
		/*shift right all meetings from current onward*/		
		for (i=c->amount-1; i>=insert_index; i--)
			c->day[i+1] = c->day[i];
		c->day[insert_index] = m;
	
	}
	c->amount++;
	return 1;
}


Meeting_t* findMeeting(Calendar_t* c, float begin){
	int i;
	if (begin>=0 && begin<24 && c!=NULL && c->day!=NULL)
		for (i=0; i<c->amount; i++)
			if (c->day[i]->begin == begin)
				return c->day[i];
	return NULL;
}


void removeMeeting(Calendar_t* c, float begin){
	Meeting_t* m;	
	int i, j;
	
	if (begin<0 || begin>=24 || c==NULL || c->day==NULL)
		return;
	for (i=0; i < c->amount; i++){
		if (c->day[i]->begin > begin)
			return;
		if (c->day[i]->begin == begin){
			for (j=i+1; j < c->amount; j++){
				c->day[j-1] = c->day[j];
			}
			c->amount--;
			break;
		}
	}
	return;
}


void destroyAD(Calendar_t* c){
	int i;	
	if (c != NULL){
		if (c->day != NULL){
			for (i=0; i<c->amount; i++)
				free(c->day[i]);
		}
		free(c->day);
		free (c);
	}
}


void printAD(Calendar_t* c){
	int i=0;
	if (c==NULL || c->day==NULL){
		printf("printing failed\n");
		return;
	}
	printf("amount:%d . your day: \n",c->amount);
	for (i=0; i<c->amount; i++){
		if (c->day[i] != NULL)
			printf("meeting from %f until %f in room no. %d\n", c->day[i]->begin, c->day[i]->end, c->day[i]->room);
		else{
			printf("printing failed\n");
			return;
		}
	}
}


int loadFromFile(Calendar_t* c){
	FILE* fp;
	float start, finish;
	int room;
	Meeting_t* m;
	
	fp = fopen(Calendar_name, "r");
	if (fp == NULL)
		return 1;
	while (1){
		fscanf(fp, "%f%f%d", &start, &finish, &room);
		if(!feof(fp)){
			m = createMeeting(start, finish, room);
			if (!m || !insertMeeting(c, m))
				return 0;
		}
		else break;	
	}
	if (fclose(fp) != 0)
		return 0;
	return 1;
}


int saveInFile(Calendar_t* c){
	FILE* fp;
	int i;

	if (!(fp = fopen(Calendar_name, "w")) || c==NULL)
		return -1;
	for (i=0; i<c->amount; i++)
		fprintf(fp, "%f %f %d\n", c->day[i]->begin, c->day[i]->end, c->day[i]->room);
	if (fclose(fp) != 0)
		return 0;
	return 1;

}
