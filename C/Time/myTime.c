#include<stdlib>
#include<stdio.h>

cTime_t* createTime(int h, int m, int s){
	cTime_t* t;
	if (h>24 || h<0 || m<0 || m>59 || s<0 || s>59){
		perror("invalid param");
		return NULL;
	t = (cTime_t*)malloc(sizeof(cTime_t));
	if (t == NULL)
		return NULL;
	t->hours = (h==24?0:h);
	t->minutes = m;
	t->secondes = s;
	return t;
}

cTime_t* setTime(cTime_t* t, int h, int m, int s){
	if (h>24 || h<0 || m<0 || m>59 || s<0 || s>59){
		perror("invalid param");
		return NULL;
	t->hours = (h==24?0:h);
	t->minutes = m;
	t->secondes = s;
	return t;
}

int getHour(constcTime_t* t);
int getMinute(const cTime_t* t);
int getSecond(const cTime_t* t);

