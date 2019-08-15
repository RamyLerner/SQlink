#ifndef MYTIME_H
#define MYTIME_H
	
	struct cTime{
		int seconds;
		int minutes;
		int hours;
	};
	typedef struct cTime cTime_t; 

	

	cTime_t* createTime(int h, int m, int s);	
	cTime_t* setTime(cTime_t* t, int h, int m, int s);
	void printTime(cTime_t* t, int format);
	int getHour(cTime_t* t);
	int getMinute(cTime_t* t);
	int getSecond(cTime_t* t);
	cTime_t* addTimes(cTime_t* t1, const cTime_t* t2);
	void destroyTime(cTime_t*);
	
#endif
