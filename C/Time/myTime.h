#ifndef MYTIME_H
#define MYTIME_H
	
	struct cTime{
		int seconds;
		int minutes;
		int hours;
	}
	typedef struct cTime cTime_t; 

	struct cDate{
		int day;
		int month;
		int year;
	}
	typedef struct cDate cDate_t;

	cTime_t* createTime(int h, int m, int s);	
	cTime_t* setTime(cTime_t* t, int h, int m, int s);
	void printTime(cTime_t* t, int format);
	int getHour(constcTime_t* t);
	int getMinute(const cTime_t* t);
	int getSecond(const cTime_t* t);
	cTime_t* addTimes(cTime_t* t1, const cTime_t* t2);
	void destroyTime(cTime_t*);

	
	cDate_t* createDate(int d, int m, int y);	
	cDate_t* setDate(cDate_t* date, int d, int t, int y);
	void printDate(cDate_t* d, int format)
	int getHour(const cDate_t* d);
	int getMinute(const cDate_t* d);
	int getSecond(const cDate_t* d);
	cDate_t* addDates(cDate_t* t1, const cDate_t* t2);
	void destroyDate(cDate_t*);
	
#endif
