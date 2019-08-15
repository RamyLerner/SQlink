#ifndef MYDATE_H
#define MYDATE_H

	struct cDate{
		int day;
		int month;
		int year;
	};
	typedef struct cDate cDate_t;


	cDate_t* createDate(int d, int m, int y);	
	cDate_t* setDate(cDate_t* date, int d, int t, int y);
	void printDate(cDate_t* d, int format);
	int getYear(cDate_t* d);
	int getMonth(cDate_t* d);
	int getDay(cDate_t* d);
	int dayOfYear(cDate_t* da);
	int isLeap(cDate_t* da);
	char* monthName(cDate_t* da, char* name);
	cDate_t* addDates(cDate_t* t1, const cDate_t* t2);
	void destroyDate(cDate_t*);

#endif
