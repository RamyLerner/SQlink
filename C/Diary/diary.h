#define N 3
#ifndef DIARY_H
#define DIARY_H
	struct meeting{
		float begin;
		float end;
		int room;
	};
	typedef struct meeting Meeting_t;

	struct calendar{
		Meeting_t** day;
		int capacity;
		int amount;
	};
	typedef struct calendar Calendar_t;

	
	Calendar_t* createAD();
	Meeting_t* createMeeting(float begin, float end, int room);
	int insertMeeting(Calendar_t* c, Meeting_t* m);
	Meeting_t* findMeeting(Calendar_t* c, float begin);
	void removeMeeting(Calendar_t* c, float begin);
	void destroyAD(Calendar_t* c);
	void printAD(Calendar_t* c);

#endif
