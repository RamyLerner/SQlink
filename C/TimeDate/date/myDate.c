#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"myDate.h"


static int daysPerMonth(int m, int y){
	switch (m){
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12: return 31;
		case 2: return (y%4==0)?29:28;
		case 4:
		case 6:
		case 9:
		case 11: return 30;
		default: return -1;
	}
	
}

static checkDate(int d, int m, int y){	
	return (d>daysPerMonth(m,y) || d<0 || m <0 || m>12)?0:1;
}


cDate_t* createDate(int d, int m, int y){
	cDate_t* da;
	if (!checkDate(d, m ,y)){
		printf("invalid param\n");
		return NULL;
	}
	da = (cDate_t*)malloc(sizeof(cDate_t));
	if (da == NULL)
		return NULL;
	da->day = d;
	da->month = m;
	da->year = y;
	return da;
}


cDate_t* setDate(cDate_t* da, int d, int m, int y){
	if (!checkDate(d, m ,y)){
		printf("invalid param\n");
		return NULL;
	}
	da->day = d;
	da->month = m;
	da->year = y;
	return da;
}

 
int getDay(cDate_t* da){
	return da->day;
}

int getMonth(cDate_t* da){
	return da->month;
}

int getYear(cDate_t* da){
	return da->year;
}

int dayOfYear(cDate_t* da){
	int i,sum = 0;
	for (i=1; i < da->month; i++){
		sum += daysPerMonth(i, da->year);
	}
	sum += da->day;
	return sum;
}

int isLeap(cDate_t* da){
	return da->year%4 == 0;
}

char* monthName(cDate_t* da, char* name){
	switch (da->month){
		case 1: strcpy(name,"January");
			break;
		case 2: strcpy(name,"February");
			break;
		case 3: strcpy(name,"March");
			break;
		case 4: strcpy(name,"April");
			break;
		case 5: strcpy(name,"May");
			break;
		case 6: strcpy(name,"June");
			break;
		case 7: strcpy(name,"July");
			break;
		case 8: strcpy(name,"August");
			break;
		case 9: strcpy(name,"September");
			break;
		case 10: strcpy(name,"October");
			break;
		case 11: strcpy(name,"November");
			break;
		case 12: strcpy(name,"December");
			break;
		default: strcpy(name,"oops");
	}
	return name;
}

void printDate(cDate_t* da, int format){
	char month3[4],name[9];
	if(da == NULL){
		printf("invalid time\n");
		return;
	}
	switch (format){
		case 1: strncpy(month3, monthName(da, name), 3);
			month3[3] = '\0';
			printf("%d/%s/%d\n", da->day, month3, da->year);
			break;
		case 2: printf("%02d/%02d/%04d\n", da->day, da->month, da->year);
			break;
		case 3: printf("%02d/%02d/%04d\n", da->month, da->day, da->year);
			break;
		default: printf("invalid format\n");
	}
}

cDate_t* addDates(cDate_t* da1, const cDate_t* da2){
	int sumD, sumM, sumY;
	sumD = da1->day + da2->day;
	sumM = da1->month;
	sumY = da1->year;
	while (sumD > daysPerMonth(sumM, da1->year)){
		sumD %= daysPerMonth(sumM, da1->year);
		sumM++;
		if (sumM >= 13){
			sumY++;
			sumM %= 12;
		}
	}
	

	return setDate(da1, sumD, sumM, sumY);
}

void destroyDate(cDate_t* da){
	free(da);
}
