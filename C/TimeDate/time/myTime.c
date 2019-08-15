#include<stdlib.h>
#include<stdio.h>
#include"myTime.h"


static int checkTime(int h, int m, int s){
	return (h>24 || h<0 || m<0 || m>59 || s<0 || s>59)?0:1;
}

cTime_t* createTime(int h, int m, int s){
	cTime_t* t;
	if (!checkTime(h, m ,s)){
		printf("invalid param\n");
		return NULL;
	}
	t = (cTime_t*)malloc(sizeof(cTime_t));
	if (t == NULL)
		return NULL;
	t->hours = (h==24?0:h);
	t->minutes = m;
	t->seconds = s;
	return t;
}


cTime_t* setTime(cTime_t* t, int h, int m, int s){
	if (!checkTime(h, m ,s)){
		printf("invalid param\n");
		return NULL;
	}
	t->hours = (h==24?0:h);
	t->minutes = m;
	t->seconds = s;
	return t;
}


int getHour(cTime_t* t){
	return t->hours;
}

int getMinute(cTime_t* t){
	return t->minutes;
}

int getSecond(cTime_t* t){
	return t->seconds;
}


void printTime(cTime_t* t, int format){
	if(t == NULL){
		printf("invalid time");
		return;
	}
	switch (format){
		case 1: printf("%d:%d:%d\n", t->hours, t->minutes, t->seconds);
			break;
		case 2: if (t->hours >= 1 && t->hours < 12)
				printf("%d:%d:%d AM\n", t->hours, t->minutes, t->seconds);
			else if (t->hours >= 13 && t->hours < 24)
				printf("%d:%d:%d PM\n", t->hours - 12, t->minutes, t->seconds);
			else if (t->hours == 0)
				printf("%d:%d:%d AM\n", t->hours + 12, t->minutes, t->seconds);
			else if (t->hours == 12)
				printf("%d:%d:%d PM\n", t->hours, t->minutes, t->seconds);
			break;
		default: printf("invalid format\n");
	}
}

cTime_t* addTimes(cTime_t* t1, const cTime_t* t2){
	int sumH, sumM, sumS;
	sumH = t1->hours + t2->hours;
	sumM = t1->minutes + t2->minutes;
	sumS = t1->seconds + t2->seconds;
	if (sumS >= 60){
		sumM += sumS/60;
		sumS %= 60;
	}
	if (sumM >= 60){
		sumH += sumM/60;
		sumM %= 60;
	}
	if (sumH>=24)
		sumH%=24;
	return setTime(t1, sumH, sumM, sumS);
}

void destroyTime(cTime_t* t){
	free(t);
}








